// #include "C:/Wichtig/System/Static/Library/WindowEngine.h"
// #include "C:/Wichtig/System/Static/Library/Victor2.h"
// #include "C:/Wichtig/System/Static/Library/Vdctor2.h"
// #include "C:/Wichtig/System/Static/Library/Complex.h"
// #include "C:/Wichtig/System/Static/Library/TransformedView.h"
// #include "C:\Wichtig\System\Static\Container\Vector.h"

#include "/home/codeleaded/System/Static/Library/WindowEngine.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"


#define WORLD_X			200
#define WORLD_Y			200
#define WORLD_DELTA		(1.0f / 120.0f)

#define WORLD_INVALID	255U
#define WORLD_NONE		0U
#define WORLD_STATIC	1U
#define WORLD_YELLOW	2U
#define WORLD_RED		3U
#define WORLD_BLUE		4U
#define WORLD_GREEN		5U

Pixel World_Color[] = {
	BLACK,
	GRAY,
	YELLOW,
	RED,
	BLUE,
	GREEN
};

Timepoint last;
u8* world;
TransformedView tv;

char World_Static(u8 c){
	return c == WORLD_INVALID || c == WORLD_NONE || c == WORLD_STATIC;
}
char World_Drain(u8 c,u8 t){
	return !World_Static(t) && t < c;
}
u8 World_Get(u8* world,u32 x,u32 y){
	if(x>=WORLD_X || y>=WORLD_Y) return WORLD_INVALID;
	return world[y * WORLD_X + x];
}
void World_Set(u8* world,int x,int y,u8 c){
	if(x>=WORLD_X || y>=WORLD_Y) return;
	world[y * WORLD_X + x] = c;
}
void World_Update(u8* world){
	for(u32 i = WORLD_Y - 2U;i < WORLD_Y;i--){
		for(u32 j = 0U;j<WORLD_X;j++){
			const u8 c = World_Get(world,j,i);
			
			if(!World_Static(c)){
				const u8 c0 = World_Get(world,j - 1U,i + 1U);
				const u8 c1 = World_Get(world,j,i + 1U);
				const u8 c2 = World_Get(world,j + 1U,i + 1U);

				if(c1 == WORLD_NONE){
					World_Set(world,j,i,WORLD_NONE);
					World_Set(world,j,i + 1U,c);
				}else if(c0 == WORLD_NONE && c2 == WORLD_NONE){
					World_Set(world,j,i,WORLD_NONE);
					if(Random_u32_MinMax(0U,2U) == 0U)	World_Set(world,j - 1U,i + 1U,c);
					else								World_Set(world,j + 1U,i + 1U,c);
				}else if(c0 == WORLD_NONE){
					World_Set(world,j,i,WORLD_NONE);
					World_Set(world,j - 1U,i + 1U,c);
				}else if(c2 == WORLD_NONE){
					World_Set(world,j,i,WORLD_NONE);
					World_Set(world,j + 1U,i + 1U,c);
				}
				/*
				else if(World_Drain(c,c1)){
					World_Set(world,j,i,c1);
					World_Set(world,j,i + 1U,c);
				}else if(World_Drain(c,c0) && World_Drain(c,c2)){
					if(Random_u32_MinMax(0U,2U) == 0U){
						World_Set(world,j,i,c0);
						World_Set(world,j - 1U,i + 1U,c);
					}else{
						World_Set(world,j,i,c2);
						World_Set(world,j + 1U,i + 1U,c);
					}
				}else if(World_Drain(c,c0)){
					World_Set(world,j,i,c0);
					World_Set(world,j - 1U,i + 1U,c);
				}else if(World_Drain(c,c2)){
					World_Set(world,j,i,c2);
					World_Set(world,j + 1U,i + 1U,c);
				}
				*/
			}
		}
	}
}

void Setup(AlxWindow* w){
	tv = TransformedView_New((Vec2){ GetWidth(),GetHeight() });
	TransformedView_Zoom(&tv,(Vec2){ 0.01f,0.01f });

	world = (u8*)malloc(sizeof(u8) * WORLD_X * WORLD_Y);
	memset(world,0,sizeof(u8) * WORLD_X * WORLD_Y);

	last = 0U;
}
void Update(AlxWindow* w){
	tv.ZoomSpeed = (float)w->ElapsedTime;
	TransformedView_HandlePanZoom(&tv,window.Strokes,(Vec2){ GetMouse().x,GetMouse().y });
	
	const Vec2 tl = TransformedView_ScreenWorldPos(&tv,(Vec2){ 0.0f,0.0f });
	const Vec2 br = TransformedView_ScreenWorldPos(&tv,(Vec2){ GetWidth(),GetHeight() });
	
	if(Stroke(ALX_MOUSE_L).DOWN){
		Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());
		World_Set(world,m.x,m.y,WORLD_STATIC);
	}else if(Stroke(ALX_MOUSE_R).DOWN){
		Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());
		World_Set(world,m.x,m.y,WORLD_NONE);
	}else if(Stroke(ALX_KEY_1).DOWN){
		Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());
		World_Set(world,m.x,m.y,WORLD_YELLOW);
	}else if(Stroke(ALX_KEY_2).DOWN){
		Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());
		World_Set(world,m.x,m.y,WORLD_RED);
	}else if(Stroke(ALX_KEY_3).DOWN){
		Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());
		World_Set(world,m.x,m.y,WORLD_BLUE);
	}else if(Stroke(ALX_KEY_4).DOWN){
		Vec2 m = TransformedView_ScreenWorldPos(&tv,GetMouse());
		World_Set(world,m.x,m.y,WORLD_GREEN);
	}

	const Timepoint now = Time_Nano();
	const FDuration et = Time_Elapsed(last,now);
	if(et > WORLD_DELTA) World_Update(world);

	Clear(BLACK);
	
	for(int i = (int)F32_Floor(tl.y) - 1;i<(int)F32_Ceil(br.y);i++){
		for(int j = (int)F32_Floor(tl.x) - 1;j<(int)F32_Ceil(br.x);j++){
			const u8 c = World_Get(world,j,i);
			const Vec2 bg_p = TransformedView_WorldScreenPos(&tv,(Vec2){ j,i });
			const Vec2 bg_d = TransformedView_WorldScreenLength(&tv,(Vec2){ 1.0f,1.0f });
			
			if(c != WORLD_NONE && c != WORLD_INVALID)
				RenderRect(
					bg_p.x,
					bg_p.y,
					bg_d.x + 1,
					bg_d.y + 1,
					World_Color[c]
				);
		}
	}

	const Vec2 bg_r_p = TransformedView_WorldScreenPos(&tv,(Vec2){ 0.0f,0.0f });
	const Vec2 bg_r_d = TransformedView_WorldScreenLength(&tv,(Vec2){ WORLD_X,WORLD_Y });
    RenderRectWire(bg_r_p.x,bg_r_p.y,bg_r_d.x,bg_r_d.y,WHITE,1.0f);
}
void Delete(AlxWindow* w){
    if(world) free(world);
	world = NULL;
}

int main(){
    if(Create("Falling Sand",2200,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}