#include <stdio.h>


void cipher(const char* key, const char* msg, char* res)
{
  unsigned i = 0;
  unsigned j = 0;
  while (msg[i] != '\0')
  {
    char c = msg[i];
    char k = key[j];

    if (c >= 'a' && c <= 'z')
      c -= 'a' - 'A';
    if (k >= 'a' && k <= 'z')
      k -= 'a' - 'A';

    if (c >= 'A' && c <= 'Z')
    {
      c -= 'A';
      k -= 'A';
      c = (c + k) % 26;
      c += 'A';
    }

    res[i] = c;

    i++;
    j++;
    if (key[j] == '\0')
      j = 0;
  }

  return;
}

void decipher(const char* key, const char* msg, char* res)
{
  unsigned i = 0;
  unsigned j = 0;
  while (msg[i] != '\0')
  {
    char c = msg[i];
    char k = key[j];

    if (c >= 'a' && c <= 'z')
      c -= 'a' - 'A';
    if (k >= 'a' && k <= 'z')
      k -= 'a' - 'A';

    if (c >= 'A' && c <= 'Z')
    {
      c -= 'A';
      k -= 'A';
      c += 26;
      c = (c - k) % 26;
      c += 'A';
    }

    res[i] = c;

    i++;
    j++;
    if (key[j] == '\0')
      j = 0;
  }

  return;
}
