#define s21_size_t unsigned long // maybe ll xz
#define s21_NULL (void *)0       // Null pointer constant.
// The macro shall expand to an integer constant expression with the value 0
// cast to type void*

s21_size_t s21_strlen(const char *str);
char *s21_strchr(const char *str, int c);
char *s21_strrchr(const char *str, int c);
char *s21_strpbrk(const char *str1, const char *str2);
void *s21_memchr(const void *str, int c, s21_size_t n);