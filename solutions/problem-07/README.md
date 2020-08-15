# 7. Reverse Integer
### Description
Given a 32-bit signed integer, reverse digits of an integer.

### First intuitions
One way to extract the last digit of an integer is by using the modulus operator:

```cpp
int x = 1337;
int last_digit = x % 10; // results in 7
```

Perhaps we can leverage this knowledge iteratively extract the last digit and add it to the end of some integer variable we'll call `reversed`.

We can also get rid of the last digit of an integer by dividing it by `10`.

```cpp
int x = 1337;
int no_last_digit = x / 10; // results in 133
```
Now we have two powerful pieces of information that can help us to iteratively extract the last digit, store it somewhere, remove it, and repeat the process again until we have no digits left.

### Solution
The first step is to initialize an integer variable to store the reversed integer.

```cpp
int reverse(int x) {
    int reversed = 0;
}
```

Next, we want to iterate as many times as there are digits in `x`. Since we are making use of the tools we mentioned in our first intuitions, we know that there are no digits left once `x = 0`. That is because once the last digit is stripped (i.e divided by `10`), for example `1`, the division operation truncates the result, which would be a decimal, to `0`. So, we only want to iterate if `x` is greater than `0`. Using a `while` loop is perfect for this.

```cpp
while (x > 0) {
    ...
}
```
Using the information from our first intuitions, let's extract the last digit in `x`, store it somewhere, and then remove it from `x`.

```cpp
while (x > 0) {
    int last_digit = x % 10; // Extract last digit
    x /= 10; // Remove last digit
}
```

Now, what do we do with the last digit we stored? We could add it to `reversed`, but in the following iteration, the last two digits will be summed! That's not the behavior we're looking for. One way to solve this is by multiplying `reversed` by `10`, to get an empty slot at the end of `reversed`! For instance, if `reversed = 13`, multiplying it by `10` would yield `130`. Now, if we add any digit to `reversed`, we would effectively append a last digit to the original `reversed` value.
```cpp
reversed *= 10;
reversed += last_digit;
```

Finally, we want to return `reversed`. So far, we have the following:

```cpp
int reverse(int x) {
        int reversed = 0;

        while (x > 0) {
            int last_digit = x % 10; // Extract last digit
            x /= 10; // Remove last digit

            reversed *= 10;
            reversed += last_digit;
        }

        return reversed;
}
```

### Edge cases

With the code we have, we fail to account for negative values. To fix this, we create an integer variable that stores the sign of `x`. We set `x` to be its absolute value, and deal with it as a positive integer. Before we return `reversed`, however, we need to multiply it by its sign. Here's how I do that:

```cpp
int reverse(int x) {
        int sign = x > 0 ? 1 : -1;
        x = abs(x);

        ....

        return reversed * sign;
}
```
The second edge case that we don't account for is when the reversed integer cannot be stored in a 32-bit signed integer representation. One example of this is `INT_MAX = 2,147,483,647`. The reverse value cannot be stored as a 32-bit integer, and the fastest way to check this is by looking at the last digit, which is `7`. It is greater than `2`, which is the maximum first digit for a 10-digit long number.

The integer overflow first happens when we multiply `reversed` by `10`. To fix this, we can ensure that `reversed` isn't greater than `INT_MAX / 10`, because if it was, multiplying it by 10 would result in something greater than `INT_MAX`! In this case, we want to return `0`, as the problem notes say.


```cpp
int reverse(int x) {
        ...
        while (x > 0) {
            if (reversed > INT_MAX / 10) {
                return 0;
            }
            ...
        }
        ...
}
```

### Complete solution
Here's the code for my submitted solution:
```cpp
int reverse(int x) {
    // Store sign and strip it from x
    int sign = x > 0 ? 1 : -1;
    x = abs(x);

    int reversed = 0;

    // Iterate until there are no digits left
    while (x > 0) {
        // If multiplying reversed by 10 will cause an
        // integer overflow, return 0
        if (reversed > INT_MAX / 10) {
            return 0;
        }
        
        // Extract last digit and strip it from x
        int last_digit = x % 10;
        x /= 10;

        // Append last_digit to reversed
        reversed *= 10;
        reversed += last_digit;
    }

    return reversed * sign;
}
```