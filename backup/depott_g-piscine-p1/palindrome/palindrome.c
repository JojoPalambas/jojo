#include <stdio.h>

int is_az09(char a)
{
  return ((a >= '0' && a <= '9') || (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'));
}

int palindrome(const char* s)
{
  int end = 0;
  while (s[end] != '\0')
    end++;
  end--;

  int is_pal = 1;
  int start = 0;
  while (is_pal == 1 && start < end)
  {
    if (!is_az09(s[start]))
      start++;
    else if (!is_az09(s[end]))
      end--;
    else if (s[start] != s[end])
      is_pal = 0;
    else
    {
      start++;
      end--;
    }
  }

  return is_pal;
}
