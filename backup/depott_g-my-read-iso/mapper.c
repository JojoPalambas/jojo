#include "include.h"

struct iso_prim_voldesc *mapper(char *path)
{
  int ans = 0;

  int fd = open(path, O_RDONLY);
  if (fd < 0)
    err(1, "File can't be opened");
  struct stat stat;
  ans = fstat(fd, &stat);
  if (ans == -1)
    err(1, "Stat structure can't be got using the file descriptor");

  void *ptr = mmap(NULL, stat.st_size,
                   PROT_READ, MAP_PRIVATE,
                   fd, 0);
  if (!ptr)
    err(1, "Mapping can't be done");

  char *tmp = ptr;
  tmp += ISO_PRIM_VOLDESC_BLOCK * ISO_BLOCK_SIZE;
  ptr = tmp;

  struct iso_prim_voldesc *iso = ptr;

  close(fd);

  return iso;
}

int sanity_check(struct iso_prim_voldesc *iso)
{
  if (!iso)
    return 0;

  return 1;
}

void info(struct iso_prim_voldesc *iso)
{
  printf("System Identifier: %s\n", iso->syidf);
  printf("Volume Identifier: %s\n", iso->vol_idf);
  printf("Block count: %u\n", iso->vol_blk_count.le); // endian32
  printf("Block size: %u\n", iso->vol_blk_size.le);   // endian16
  printf("Creation date: %s\n", iso->date_creat);
  printf("Application Identifier: %.*s\n", ISO_APP_LEN, iso->app_idf);
}

void dir_info(struct iso_prim_voldesc *iso)
{
  struct iso_dir dir = iso->root_dir;

  printf("%u\n", dir.dir_size);
  printf("%u\n", dir.ext_size);
  printf("%u\n", dir.data_blk.le);
  printf("%u\n", dir.file_size.le);
  printf("%s\n", dir.date);
  printf("%u\n", dir.type);
  printf("%u\n", dir.unit_size);
  printf("%u\n", dir.gap_size);
  printf("%u\n", dir.vol_seq.le);
  printf("%u\n", dir.idf_len);
}

void ls_test(struct iso_prim_voldesc *iso)
{
  struct iso_dir *dir = &iso->root_dir;

  while (dir->dir_size != 0)
  {
    printf("%u\n", dir->dir_size);

    void *tmp = dir;
    char *tmpc = tmp;
    tmpc += dir->dir_size;
    tmp = tmpc;
    dir = tmp;
  }
}

void ls(struct iso_prim_voldesc *iso)
{
  uint32_t path_size = iso->path_table_size.le;
  uint32_t path_blk = iso->le_path_table_blk;

  struct iso_path_table_le *path_table = ;
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("usage: %s FILE\n", argv[0]);
    return 1;
  }

  struct iso_prim_voldesc *iso = mapper(argv[1]);

  if (!sanity_check(iso))
    err(1, "Sanity check failed");

  info(iso);

  ls(iso);
}
