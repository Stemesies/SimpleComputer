
typedef enum keys
{
  K_1 = '1',
  K_2 = '2',
  K_3 = '3',
  K_4 = '4',
  K_5 = '5',
  K_6 = '6',
  K_7 = '7',
  K_8 = '8',
  K_9 = '9',
  K_0 = '0',
  K_a = 'a',
  K_i = 'i',
  K_l = 'l',
  K_r = 'r',
  K_s = 's',
  K_t = 't',
  K_z = 'z',
  K_A = 'A',
  K_Z = 'Z',
  K_plus = '+',
  K_minus = '-',
  K_esc = 27,
  K_left = 4479771,
  K_up = 4283163L,
  K_down = 4348699L,
  K_right = 4414235,
  K_F5 = 892427035L,
  K_F6 = 925981467L,
  K_enter = 10,
  K_backspace = 127
} Keys;

void rk_init ();
int rk_readkey (Keys *key);
int rk_mytermsave ();
int rk_mytermrestore ();
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_readvalue (int *value, int timeout);
int rk_readn (char *buffer, int n);
