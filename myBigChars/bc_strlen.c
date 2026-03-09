int
bc_strlen (char *str)
{
  int count = 0;
  while (*str)
    {
      count += ((*str & 0xc0) != 0x80);
      str++;
    }

  return count;
}