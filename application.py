import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Merge purchase data
    port_total = 0
    portfolio = []
    rows = db.execute("SELECT symbol, SUM(shares) FROM purchases WHERE user_id= ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

    # Store data into portfolio
    for row in rows:
        p_stock = lookup(row["symbol"])
        portfolio.append({
            "symbol": p_stock["symbol"],
            "name" : p_stock["name"],
            "shares": row["SUM(shares)"],
            "price": usd(p_stock["price"]),
            "total": usd(p_stock["price"] * row["SUM(shares)"])
        })

        # Tally portfolio total
        port_total += p_stock["price"] * row["SUM(shares)"]

    # Retrieve cash amount
    p_c = db.execute("SELECT cash FROM users WHERE id=?", session["user_id"])
    port_cash = p_c[0]["cash"]

    # Compute grand total, format
    grand_total = port_cash + port_total
    grand_total = usd(grand_total)
    port_cash = usd(port_cash)
    return render_template("index.html", portfolio=portfolio, port_cash=port_cash, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # If data submitted through POST
    if request.method == "POST":

        # If fields are empty, return apology
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("Missing fields")

        # Check if stock symbol is valid, then process transaction
        buy_stock = lookup(request.form.get("symbol"))
        if not buy_stock:
            return apology("Invalid stock symbol")

        # Formatting cash and purchase values
        purchase = buy_stock["price"] * int(request.form.get("shares"))
        cash_query = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        cash = int(cash_query[0]["cash"])
        cash_update = cash - purchase
        if cash_update < 0:
            return apology("Insufficient funds")

        else:
            # Record the purchase in table
            db.execute("INSERT INTO purchases(user_id, symbol, price, shares) VALUES(?, ?, ?, ?)", session["user_id"],
            buy_stock["symbol"], buy_stock["price"], request.form.get("shares"))

            # Update user's cash
            db.execute("UPDATE users SET cash = ? WHERE id=?", cash_update, session["user_id"])
            flash("Transaction complete")
            return redirect("/")

    # If data submitted through GET
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history_list = []
    rows = db.execute("SELECT symbol, shares, price, time FROM purchases WHERE user_id =?", session["user_id"])
    for row in rows:
        history_list.append({
            "symbol": row["symbol"],
            "shares": row["shares"],
            "price": row["price"],
            "time": row["time"]
        })
    return render_template("history.html", history_list=history_list)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # If data submitted through POST
    if request.method == "POST":
        stock_quote = lookup(request.form.get("symbol"))

        # If lookup succesful, convert and show info
        if stock_quote:
            return render_template("quote.html", quote = stock_quote)

    # If data submitted through GET
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # If data submitted through POST
    if request.method == "POST":

        # Return apology if user does not register properly
        if not request.form.get("username"):
            return apology("must provide username")

        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide, confirm password")

        # Return apology if passwords do not match
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("passwords do not match")

        # If form data is fulfilled
        # Query database for user
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # If user exists, return apology
        if len(rows) != 0:
            return apology("Username taken")

        else:
            # Generate password hash, insert username and hash into db
            p_hash = generate_password_hash(request.form.get("password"))
            username= request.form.get("username")
            db.execute("INSERT INTO users(username, hash) VALUES(?, ?)", username, p_hash)
            flash("Registered!")
            return render_template("login.html")

    # If data submitted through GET
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    sell_list = db.execute("SELECT DISTINCT symbol FROM purchases WHERE user_id=? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

    # If data submitted through POST
    if request.method == "POST":

        # If forms not completed, return apology
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("Missing fields")

        # Lookup symbol
        sell_stock = lookup(request.form.get("symbol"))
        sell_trans = -1 * int(request.form.get("shares"))
        sh_o = db.execute("SELECT SUM(shares) FROM purchases WHERE symbol=?", sell_stock["symbol"])
        shares_owned = sh_o[0]["SUM(shares)"]
        share_update = shares_owned - int(request.form.get("shares"))
        # If formdata exceeds shares owned, return apology
        if share_update < 0:
            return apology("Insufficient shares")

        # Record transaction in purchases
        else:
            db.execute("INSERT INTO purchases(user_id, symbol, price, shares) VALUES(?, ?, ?, ?)", session["user_id"],
            sell_stock["symbol"], sell_stock["price"], sell_trans)

            # Update user's cash
            sale = sell_stock["price"] * int(request.form.get("shares"))
            sell_query = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            cash_sell = int(sell_query[0]["cash"])
            sell_update = cash_sell + sale
            db.execute("UPDATE users SET cash = ? WHERE id=?", sell_update, session["user_id"])
            flash("Transaction successful")
            return redirect("/")

    # If data submitted through GET
    else:
        return render_template("sell.html", sell_list=sell_list)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
