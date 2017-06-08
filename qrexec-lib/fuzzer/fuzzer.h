#ifndef FUZZER_H
#define FUZZER_H

#ifdef __cplusplus
extern "C" {
#endif
typedef void (notify_progress_t)(int, int);
typedef void (error_handler_t)(const char *fmt, va_list args);
void register_notify_progress(notify_progress_t *func);
void register_error_handler(error_handler_t *func);

/* common functions */
int copy_file(int outfd, int infd, long long size, unsigned long *crc32);
const char *copy_file_status_to_str(int status);
void set_size_limit(unsigned long long new_bytes_limit, unsigned long long new_files_limit);
void set_verbose(int value);
/* register open fd to /proc/PID/fd of this process */
void set_procfs_fd(int value);
int write_all(int fd, const void *buf, int size);
int read_all(int fd, void *buf, int size);
int copy_fd_all(int fdout, int fdin);
void set_nonblock(int fd);
void set_block(int fd);

/* unpacking */
extern unsigned long Crc32_ComputeBuf( unsigned long inCrc32, const void *buf,
        size_t bufLen );
extern int do_unpack(void);

/* packing */
int single_file_processor(const char *filename, const struct stat *st);
int do_fs_walk(const char *file, int ignore_symlinks);
/* used in tar2qfile to alter only headers, but keep original file stream */
void write_headers(const struct file_header *hdr, const char *filename);
int copy_file_with_crc(int outfd, int infd, long long size);
/* MUST be called before first do_fs_walk/single_file_processor */
void qfile_pack_init(void);
void set_ignore_quota_error(int value);
/* those two will call registered error handler if needed */
void wait_for_result(void);
void notify_end_and_wait_for_result(void);

#ifdef __cplusplus
}
#endif

#endif
