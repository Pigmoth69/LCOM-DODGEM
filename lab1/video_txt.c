#include <minix/drivers.h>
#include <sys/video.h>
#include <sys/mman.h>

#include <assert.h>

#include "vt_info.h"

#include "video_txt.h"

/* Private global variables */

static char *video_mem;		/* Address to which VRAM is mapped */

static unsigned scr_width;	/* Width of screen in columns */
static unsigned scr_lines;	/* Height of screen in lines */

void vt_fill(char ch, char attr)
{
		char *PointerRam;
		PointerRam = video_mem;
		int x;
		for(x = 0 ; x < scr_width*scr_lines;x++)
		{
			*PointerRam =ch;
			PointerRam++;
			*PointerRam=attr;
			PointerRam++;
		}
}

void vt_blank() {

	char *PointerRam;
	PointerRam = video_mem;
	int x;
	for(x = 0 ; x < scr_width*scr_lines;x++)
	{
		*PointerRam =' ';
		PointerRam++;
		*PointerRam=07;
		PointerRam++;
	}

}

int vt_print_char(char ch, char attr, int r, int c)
{
			char *PointerRam;
			PointerRam = video_mem;

			if(r >= scr_width || c >= scr_lines)
			{
				return 1;
			}

				PointerRam = PointerRam + 2*(r*scr_width-(scr_width-c))-2;
				*PointerRam =ch;
				PointerRam++;
				*PointerRam=attr;
				return 0;
}


int vt_print_string(char *str, char attr, int r, int c)
{
				char *PointerRam;
				PointerRam = video_mem;
				int i ;
				int lim = strlen(str);

				if(r >= scr_width || c >= scr_lines)
				{
					return 1;
				}

					PointerRam = PointerRam + 2*(r*scr_width-(scr_width-c))-2;
					for(i = 0; i < lim ;i++)
					{
						*PointerRam = *(str+i);
						PointerRam++;
						*PointerRam=attr;
						PointerRam++;
						// falta
					}

					return 0;

}

int vt_print_int(int num, char attr, int r, int c) {

				char *PointerRam;
				PointerRam = video_mem;
				char numero_char= ' ';
				int comprimento = 0;
				int numero = num;

				if(r >= scr_width || c >= scr_lines)
								{
									return 1;
								}

				int x;
				while(numero % 10 != 0)
				{
					numero = numero / 10;
					comprimento++;
				}
				PointerRam = PointerRam + 2*(r*scr_width-(scr_width-c))-2;
				for(x = 0; x < comprimento;x++)
				{
							numero_char +=
				}
				*PointerRam =numero;
				PointerRam++;
				*PointerRam=attr;
				return 0;








}


int vt_draw_frame(int width, int height, char attr, int r, int c)
{

  /* To complete ... */

}

/*
 * THIS FUNCTION IS FINALIZED, do NOT touch it
 */

char *vt_init(vt_info_t *vi_p) {

  int r;
  struct mem_range mr;

  /* Allow memory mapping */

  mr.mr_base = (phys_bytes)(vi_p->vram_base);
  mr.mr_limit = mr.mr_base + vi_p->vram_size;

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
	  panic("video_txt: sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vi_p->vram_size);

  if(video_mem == MAP_FAILED)
	  panic("video_txt couldn't map video memory");

  /* Save text mode resolution */

  scr_lines = vi_p->scr_lines;
  scr_width = vi_p->scr_width;

  return video_mem;
}
