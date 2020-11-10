#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Creating variable [name]
    string name;
    
    // Requesting string value for variable [name]
    name = get_string("What's your name?\n");
    
    // Displaying variable [name] within preset phrase
    printf("hello, %s\n", name);

}