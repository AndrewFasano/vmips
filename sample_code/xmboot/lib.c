/* The little C library. */

#include <stdarg.h>
#include "lib.h"

int errno;

static short modes;

int
set_echo (int onoff)
{
  term_disable (ECHO);
  if (onoff)
    term_enable (ECHO);
}

int
term_enable (int mode)
{
  modes |= mode;
}

int
term_disable (int mode)
{
  modes &= ~mode;
}

int
getchar (void)
{
  char ch;
  int rv;

  rv = read (0, &ch, 1);
  if (rv != 1)
    {
      return -1;
    }
  else
    {
      if ((modes & ICRNL) && (ch == '\r'))
        ch = '\n';
      if (modes & ECHO)
        putchar (ch);
      return ch;
    }
}

int
putchar (unsigned char ch)
{
  if ((modes & ONLCR) && (ch == '\n'))
    putchar ('\r');
  return ((write (1, &ch, 1) < 1) ? -1 : 0);
}

void
puts_nonl (const char *buf)
{
  while (*buf)
    {
      putchar (*buf++);
    }
}

char *
gets (char *buf)
{
  char ch;
  char *rv = buf;
  while (1)
    {
      if ((ch = getchar ()) < 0)
        return NULL;
      if (!(ch == '\n' || ch == '\r'))
        {
          *buf++ = ch;
        }
      else
        {
          break;
        }
    }
  *buf++ = '\0';
  return rv;
}

int
puts (const char *buf)
{
  puts_nonl (buf);
  putchar ('\n');
}

int
strcmp (const char *s1, const char *s2)
{
  const char *p = s1;
  const char *q = s2;

  while ((*p != '\0') || (*q != '\0'))
    {
      if (*p != *q)
        return (*p - *q);
      p++;
      q++;
    }
  return 0;
}

int
strlen (const char *s)
{
  int length = 0;

  while (*s++)
    length++;
  return length;
}

static int
char_to_digit (const char s)
{
  if (s >= '0' && s <= '9')
    {
      return s - '0';
    }
  if (s >= 'a' && s <= 'z')
    {
      return 10 + (s - 'a');
    }
  if (s >= 'A' && s <= 'Z')
    {
      return 10 + (s - 'A');
    }
  return 0;
}

char
toupper (char c)
{
  if (c >= 'a' && c <= 'z')
    {
      return (c - 'a') + 'A';
    }
  else
    return c;
}

char
tolower (char c)
{
  if (c >= 'A' && c <= 'Z')
    {
      return (c - 'A') + 'a';
    }
  else
    return c;
}

char
digit_to_char (unsigned int digit, unsigned int use_uppercase)
{
  const char lowercase_digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
  char c;

  c = lowercase_digits[digit];
  if (use_uppercase)
    c = toupper (c);
  return c;
}

int
isspace (const char c)
{
  return (c == ' ') || (c == '\t') || (c == '\r') || (c == '\n');
}

int
isdigit (const char c)
{
  return ((c >= '0') && (c <= '9'));
}

int
isprint (const char c)
{
  /* this is really crude, but works for most of 7-bit ASCII */
  return ((c >= 32) && (c < 127));
}

long
strtol (const char *s, char **endptr, int radix)
{
  int num = 0, length, i = 0, negate = 0;

  while (isspace (*s))
    s++;

  if (radix == 0)
    {
      if (s[0] == '0')
        {
          if (s[1] == 'x')
            {
              s += 2;
              radix = 16;
            }
          else if (s[1] == '\0')
            {
              return 0;
            }
          else
            {
              s += 1;
              radix = 8;
            }
        }
      else if (isdigit (s[0]) || s[0] == '-')
        {
          radix = 10;
        }
      else
        {
          return 0;
        }
    }
  if (s[0] == '-')
    {
      negate = 1;
      s++;
    }
  length = strlen (s);
  do
    {
      num *= radix;
      num += char_to_digit (s[i]);
      i++;
    }
  while (i < length);
  if (negate)
    num = -num;
  return num;
}

static int
print_int (int i, unsigned int radix, unsigned int use_uppercase)
{
  char digit = digit_to_char (i % radix, use_uppercase);
  int remains = (i / radix);

  if (i < 0)
    {
      putchar ('-');
      return 1 + print_int (-i, radix, use_uppercase);
    }
  else if (remains > 0)
    {
      int nprinted = print_int (remains, radix, use_uppercase);
      putchar (digit);
      return 1 + nprinted;
    }
  else
    {
      putchar (digit);
      return 1;
    }
}

static int
print_unsigned_int (unsigned int i, unsigned int radix,
                    unsigned int use_uppercase)
{
  char digit = digit_to_char (i % radix, use_uppercase);
  int remains = (i / radix);

  if (remains > 0)
    {
      int nprinted = print_unsigned_int (remains, radix, use_uppercase);
      putchar (digit);
      return 1 + nprinted;
    }
  else
    {
      putchar (digit);
      return 1;
    }
}

int
printf (const char *fmt, ...)
{
  const char *f = fmt;
  va_list ap;
  int count = 0;
  int nextarg_is_long = 0;
  int i;
  unsigned int u;
  char c;
  char *s;

  va_start (ap, fmt);
  while (f[0])
    {
      if (f[0] != '%')
        {
          putchar (*f);
          count += 1;
          f += 1;
        }
      else
        {
          if (f[1] == 'l') { nextarg_is_long++; f++; }
          switch (f[1])
            {
            case 'c':
              c = (char) va_arg (ap, int);
              putchar (c);
              count += 1;
              break;
            case 'd':
            case 'i':
              i = va_arg (ap, int);
              count += print_int (i, 10, 0);
              break;
            case 'o':
              u = (unsigned int) va_arg (ap, int);
              count += print_unsigned_int (u, 8, 0);
              break;
            case 'u':
              u = (unsigned int) va_arg (ap, int);
              count += print_unsigned_int (u, 10, 0);
              break;
            case 'x':
              u = (unsigned int) va_arg (ap, int);
              count += print_unsigned_int (u, 16, 0);
              break;
            case 'X':
              u = (unsigned int) va_arg (ap, int);
              count += print_unsigned_int (u, 16, 1);
              break;
            case 's':
              s = (char *) va_arg (ap, char *);
              while (*s)
                {
                  putchar (*s++);
                  count++;
                }
              break;
            default:
              putchar (f[1]);
              count += 1;
              break;
            }
          f += 2;
        }
    }
  return count;
}

char *
strcpy(char *dest, const char *src)
{
  char *rv = dest;

  do {
	  *dest++ = *src++;
  } while (*src);
  *dest++ = '\0';
  return rv;
}

void *
memcpy (void *dest, const void *src, size_t n)
{
  void *rv = dest;
  char *dest_c = (char *) dest;
  char *src_c = (char *) src;

  while (n--)
    {
      *dest_c++ = *src_c++;
    }
  return rv;
}

void *
memmove (void *dest, const void *src, size_t n)
{
  void *rv = dest;
  unsigned char *dest_c = (unsigned char *) dest;
  unsigned char *src_c = (unsigned char *) src;

  if (dest_c - src_c < 0) {
    /* Copy forwards. */
    while (n--)
      {
        *dest_c++ = *src_c++;
      }
  } else if (dest_c - src_c > 0) {
    /* Copy backwards. */
    dest_c += n;
    src_c += n;
    while (n--)
      {
        *--dest_c = *--src_c;
      }
  }
  return rv;
}

void *
memset(void *s, int c, size_t n)
{
  unsigned char *dest_c = (char *) s;
  void *rv = s;
  unsigned char c_c = c;

  while (n--)
    {
      *dest_c++ = c_c;
    }
  return rv;
}

