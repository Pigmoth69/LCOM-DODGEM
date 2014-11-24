#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>

#include "vbe.h"
#include "lmlib.h"

#define LINEAR_MODEL_BIT 14

#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)






int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {


	char *video_memory= lm_init();
	mmap_t map;


	lm_alloc(sizeof(vbe_mode_info_t), &map);


	struct reg86u rx;

	rx.u.w.ax = 0x4F00;
	rx.u.w.es = PB2BASE(map.phys);
	rx.u.w.di = PB2OFF(map.phys);

	if( sys_int86(&rx) != OK ) { /* call BIOS */
		printf("error sys_int 86 vbe_get_mode_info\n");
		return 1;
	}


	*vmi_p = *(vbe_mode_info_t*)map.virtual;

	lm_free( &map);
	return *video_memory;


}


