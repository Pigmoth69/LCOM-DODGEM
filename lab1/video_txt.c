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

	if(r >= scr_lines || c >= scr_width)
	{
		return 1;
	}

	PointerRam += 2*(scr_width*r+c);

	if(PointerRam + 2*lim > video_mem+2*scr_width*scr_lines)
	{
		return -1;
	}
	for(i = 0; i < lim ;i++)
	{
		*PointerRam = *(str+i);
		PointerRam++;
		*PointerRam=attr;
		PointerRam++;

	}

	return 0;

}

int vt_print_int(int num, char attr, int r, int c)
{


	char *PointerRam;
	PointerRam = video_mem;
	int i ;
	int lim = 0;
	int numero = num;

	if(r >= scr_lines || c >= scr_width)
	{
		return 1;
	}

	PointerRam += 2*(scr_width*r+c);


	if(numero<0){
		numero=numero*(-1);
	}
	while(numero > 0)
	{
		numero = numero/10;
		lim++;
	}

	if(PointerRam + 2*lim > video_mem+2*scr_width*scr_lines)
	{
		return -1;
	}

	if( num < 0)
		{
			num=num*-1;
			*PointerRam=0x2D;
			PointerRam++;
			*PointerRam=attr;
			PointerRam++;
		}

	PointerRam+=2*(lim-1);
	for(i = 0; i < lim ;i++)
	{
		*PointerRam=0x30+num%10;
		num=num/10;
		PointerRam++;
		*PointerRam=attr;
		PointerRam-=3;

	}

	return 0;

}


int vt_draw_frame(int width, int height, char attr, int r, int c)
{

	char *PointerRam;
	PointerRam = video_mem;
	int x;


	if(r >= scr_lines || c >= scr_width || r<0||c<0 || scr_width < c+width||scr_lines < r+height)
		{
			return 1;
		}

	PointerRam += 2*(scr_width*r+c)+1;


	for(x=0;x<width; x++)
	{
		*PointerRam=attr;
		PointerRam +=2;
	}
	PointerRam -=2;
	for(x=1; x < height;x++)
	{
		PointerRam +=2*scr_width;
		*PointerRam=attr;
	}

	PointerRam -=2*width;
	PointerRam +=2;

	for(x=0; x<width;x++)
	{
		*PointerRam=attr;
		PointerRam +=2;
	}

	PointerRam = video_mem;
	PointerRam += 2*(scr_width*r+c)+1;

	for(x=0;x<height;x++)
	{
		*PointerRam = attr;
		PointerRam +=2*scr_width;
	}

	return 0;


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
