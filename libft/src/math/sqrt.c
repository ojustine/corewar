/**
* @brief Calculates a floor square root of a number.
* @param [in] n Number to calculate.
* @return Floor square root of a number @a n.
* @ingroup math
*/
int math_floor_sqrt(int n)
{
	int start;
	int end;
	int mid;
	int ans;

	if (n == 0 || n == 1)
		return (n);
	start = 1;
	end = n;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (mid * mid == n)
			return (mid);
		if (mid * mid < n)
		{
			start = mid + 1;
			ans = mid;
		}
		else
			end = mid - 1;
	}
	return (ans);
}
