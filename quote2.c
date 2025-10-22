#include "mini.h"

char	*handle_replacement(char *s, char *val, int pos, int var_len)
{
	int		len_src;
	int		len_val;
	int		len_new;
	int		len_tail;
	char	*out;

	len_src = ft_strlen(s);
	len_val = ft_strlen(val);
	len_new = len_src - var_len + len_val;
	if (len_new < 0)
		return (ft_strdup(s));
	out = safe_malloc(len_new + 1);
	if (pos > 0)
		ft_memcpy(out, s, pos);
	ft_memcpy(out + pos, val, len_val);
	len_tail = len_src - (pos + var_len);
	if (len_tail > 0)
		ft_memcpy(out + pos + len_val, s + pos + var_len, len_tail);
	out[len_new] = '\0';
	return (out);
}

//char	*handle_single_quote(char *s, int pos)
//{
//	int		len_src;
//	int		len_new;

//	len_src = ft_strlen(s);
//	len_new = 
//	if (len_new < 0)
//		return (ft_strdup(s));
//}