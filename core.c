#include "iso9660.h"
#include "include.h"

void info(struct status *st)
{
  struct iso_prim_voldesc *iso = st->iso;

  printf("System Identifier: %.*s\n", ISO_SYSIDF_LEN, iso->syidf);
  printf("Volume Identifier: %.*s\n", ISO_VOLIDF_LEN, iso->vol_idf);
  printf("Block count: %u\n", iso->vol_blk_count.le);
  printf("Block size: %u\n", iso->vol_blk_size.le);
  printf("Creation date: %.*s\n", ISO_LDATE_LEN, iso->date_creat);
  printf("Application Identifier: %.*s\n", ISO_APP_LEN, iso->app_idf);
}

void info_dir(struct iso_dir *dir, int name_type)
{
  uint8_t type = dir->type;
  if (type & ISO_FILE_ISDIR)
    printf("d");
  else
    printf("-");

  if (type & ISO_FILE_HIDDEN)
    printf("h ");
  else
    printf("- ");

  printf("%9u ", dir->file_size.le);

  printf("%04d/%02d/%02d %02d:%02d ",
         dir->date[0] + 1900,
         dir->date[1],
         dir->date[2],
         dir->date[3],
         dir->date[4]);

  if (name_type == 0)
    printf(".\n");
  else if (name_type == 1)
    printf("..\n");
  else
  {
    char *name = move(dir, sizeof (struct iso_dir));

    printf("%.*s\n", dir->idf_len - (type & ISO_FILE_ISDIR ? 0 : 2), name);
  }
}

void ls(struct status *st)
{
  struct iso_dir *dir = st->dir;
  for (int i = 0; dir->dir_size != 0; i++)
  {
    info_dir(dir, i);

    dir = move(dir, dir->dir_size);
  }
}

void cat(struct status *st)
{
  struct iso_dir *dir = &st->dir;
  for (int i = 0; dir->dir_size != 0; i++)
  {
    info_dir(dir, i);

    dir = move(dir, dir->dir_size);
  }
}
