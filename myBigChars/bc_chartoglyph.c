
char *map = "0123456789abcdef+-";

int
bc_chartoglyph (char charych)
{
  char *i = map;
  while (*i)
    {
      if (charych == *i)
        return (int)(i - map);
      i++;
    }
  return -1;
}
