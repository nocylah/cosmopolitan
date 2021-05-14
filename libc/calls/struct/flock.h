#ifndef COSMOPOLITAN_LIBC_CALLS_STRUCT_FLOCK_H_
#define COSMOPOLITAN_LIBC_CALLS_STRUCT_FLOCK_H_
#if !(__ASSEMBLER__ + __LINKER__ + 0)

struct flock {      /* cosmopolitan abi */
  int16_t l_type;   /* F_RDLCK, F_WRLCK, F_UNLCK */
  int16_t l_whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
  int64_t l_start;  /* starting offset */
  int64_t l_len;    /* 0 means until end of file */
  int32_t l_pid;    /* lock owner */
  int32_t l_sysid;  /* remote system id or zero for local */
};

#endif /* !(__ASSEMBLER__ + __LINKER__ + 0) */
#endif /* COSMOPOLITAN_LIBC_CALLS_STRUCT_FLOCK_H_ */
