void	ft_strrev(register char *begin, register char *end)
{
	register char	tmp;

	while (end > begin)
	{
		tmp = *end;
		*end-- = *begin;
		*begin++ = tmp;
	}
}
