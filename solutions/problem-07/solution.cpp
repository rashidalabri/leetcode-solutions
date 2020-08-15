class Solution {
public:
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
};