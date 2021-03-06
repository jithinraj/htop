/* Do not edit this file. It was automatically generated. */

#ifndef HEADER_Panel
#define HEADER_Panel
/*
htop - Panel.h
(C) 2004-2011 Hisham H. Muhammad
Released under the GNU GPL, see the COPYING file
in the source distribution for its full text.
*/

//#link curses

#include "Object.h"
#include "Vector.h"
#include "FunctionBar.h"

typedef struct Panel_ Panel;

typedef enum HandlerResult_ {
   HANDLED     = 0x01,
   IGNORED     = 0x02,
   BREAK_LOOP  = 0x04,
   REDRAW      = 0x08,
   RESCAN      = 0x10,
   SYNTH_KEY   = 0x20,
} HandlerResult;

#define EVENT_SET_SELECTED -1

#define EVENT_HEADER_CLICK(x_) (-10000 + x_)
#define EVENT_IS_HEADER_CLICK(ev_) (ev_ >= -10000 && ev_ <= -9000)
#define EVENT_HEADER_CLICK_GET_X(ev_) (ev_ + 10000)

typedef HandlerResult(*Panel_EventHandler)(Panel*, int);

typedef struct PanelClass_ {
   const ObjectClass super;
   const Panel_EventHandler eventHandler;
} PanelClass;

#define As_Panel(this_)                ((PanelClass*)((this_)->super.klass))
#define Panel_eventHandlerFn(this_)    As_Panel(this_)->eventHandler
#define Panel_eventHandler(this_, ev_) As_Panel(this_)->eventHandler((Panel*)(this_), ev_)

struct Panel_ {
   Object super;
   int x, y, w, h;
   WINDOW* window;
   Vector* items;
   int selected;
   int oldSelected;
   int selectedLen;
   void* eventHandlerState;
   int scrollV;
   short scrollH;
   bool needsRedraw;
   FunctionBar* currentBar;
   FunctionBar* defaultBar;
   RichString header;
   int selectionColor;
};

#define Panel_setDefaultBar(this_) do{ (this_)->currentBar = (this_)->defaultBar; }while(0)


#ifndef MIN
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef MAX
#define MAX(a,b) ((a)>(b)?(a):(b))
#endif

#define KEY_CTRL(l) ((l)-'A'+1)

extern PanelClass Panel_class;

extern Panel* Panel_new(int x, int y, int w, int h, bool owner, ObjectClass* type, FunctionBar* fuBar);

extern void Panel_delete(Object* cast);

extern void Panel_init(Panel* this, int x, int y, int w, int h, ObjectClass* type, bool owner, FunctionBar* fuBar);

extern void Panel_done(Panel* this);

extern void Panel_setSelectionColor(Panel* this, int color);

extern RichString* Panel_getHeader(Panel* this);

extern void Panel_setHeader(Panel* this, const char* header);

extern void Panel_move(Panel* this, int x, int y);

extern void Panel_resize(Panel* this, int w, int h);

extern void Panel_prune(Panel* this);

extern void Panel_add(Panel* this, Object* o);

extern void Panel_insert(Panel* this, int i, Object* o);

extern void Panel_set(Panel* this, int i, Object* o);

extern Object* Panel_get(Panel* this, int i);

extern Object* Panel_remove(Panel* this, int i);

extern Object* Panel_getSelected(Panel* this);

extern void Panel_moveSelectedUp(Panel* this);

extern void Panel_moveSelectedDown(Panel* this);

extern int Panel_getSelectedIndex(Panel* this);

extern int Panel_size(Panel* this);

extern void Panel_setSelected(Panel* this, int selected);

extern void Panel_draw(Panel* this, bool focus);

extern void Panel_splice(Panel *this, Vector* from);

extern bool Panel_onKey(Panel* this, int key);

extern HandlerResult Panel_selectByTyping(Panel* this, int ch);

#endif
