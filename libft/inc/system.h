#ifndef SYSTEM_H
# define SYSTEM_H

# include <sys/stat.h>
# include <fcntl.h>
# include <stdint.h>

enum	e_endian
{
	FT_LITTLE_ENDIAN = 0xfffe,
	FT_BIG_ENDIAN = 0xfeff
};

# ifdef WIN32
#  define	FILE_SEP_CHAR	'\\'
#  define	FILE_SEP_STR	"\\"
# else
#  define	FILE_SEP_CHAR	'/'
#  define	FILE_SEP_STR	"/"
# endif

int			ft_mkdir(const char *path);
int			ft_mkpath(const char *path);
int			ft_open_path(const char *path, int flag, mode_t mode);

enum		e_endian endian();
void		*to_sys_endian(enum e_endian from, void *pv, size_t size);
void		*to_endian(enum e_endian to, void *pv, size_t size);
void		byte_swap(void *pv, size_t size);
uint16_t	byte_swap_u16(uint16_t val);
uint32_t	byte_swap_u32(uint32_t val);
uint64_t	byte_swap_u64(uint64_t val);
int16_t		byte_swap_s16(int16_t val);
int32_t		byte_swap_s32(int32_t val);
int64_t		byte_swap_s64(int64_t val);

#endif
