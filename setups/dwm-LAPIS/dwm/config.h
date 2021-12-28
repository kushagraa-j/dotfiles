#include <X11/XF86keysym.h>

/* APPEARANCE */


static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 3;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */

static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

static const char *fonts[]          = { "googlesans:size=9.1" };
static const char dmenufont[]       = "googlesans:size=9.1";

static const char col_gray1[]       = "#222831";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#222831";
static const char col_cyan[]        = "#F05454";

static const char *colors[][3]      = {

	/*               fg         bg         border   */
 	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },

};


/* TAGGING */

static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {

	/* class           instance    title       tags mask     isfloating   monitor */
	
	/* ALL TAGS */
	{"st",              NULL,      NULL,          0,            0,          -1},

	/* Tag 2 : Browser*/
	{"firefox",         NULL,      NULL,          1 << 1,       0,          -1},

	/* Tag 3 : Chat */
	{"TelegramDesktop", NULL,      NULL,          1 << 2,       0,          -1},
	{"whatsdesk",       NULL,      NULL,          1 << 2,       0,          -1},

	/* Tag 4 : Music */
	{"cmus",            NULL,      NULL,          1 << 2,       0,          -1},

	/* Tag 5 : Study/Meeting */
	{"Microsoft Teams - Preview",  NULL,       NULL,          1 << 4,     0,          -1},
	{"zoom",                        NULL,       NULL,          1 << 4,     0,          -1},

	/* Tag 6 : System */
	{"Qemu",                        NULL,       NULL,          1 << 5,     0,          -1},
	{"Nitrogen",                    NULL,       NULL,          1 << 5,     0,          -1},

	/* Tag 9 : GFX */
	{"Gimp",            NULL,      NULL,          1 << 8,       0,          -1},

};


/* LAYOUT(S) */

static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
};


/* KEY DEFINITIONS */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* COMMANDS */

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-p" , "run" , NULL };
static const char *termcmd[]  = { "st", NULL };

static const char *ytcmd[]  = { "yt", NULL };

static const char *mutecmd[] = { "pactl", "set-sink-mute", "0", "toggle", NULL };
static const char *volupcmd[] = { "pactl", "set-sink-volume", "0", "+5%", NULL };
static const char *voldowncmd[] = { "pactl", "set-sink-volume", "0", "-5%", NULL };

static const char *brupcmd[] = { "xbacklight", "-inc", "10", NULL };
static const char *brdowncmd[] = { "xbacklight", "-dec", "10", NULL };

static const char *nextcmd[] = { "playerctl", "next", NULL };
static const char *prevcmd[] = { "playerctl", "previous", NULL };
static const char *playcmd[] = { "playerctl", "play-pause", NULL };
static const char *volcmd[] = { "pavucontrol", NULL };

static const char *lock[] = {"betterlockscreen" , "-l" , NULL };

static const char *vm[] = {"vm" , NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_y,      spawn,          {.v = ytcmd } },
	{ MODKEY,                       XK_v,      spawn,          {.v = volcmd } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = vm     } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lock }},
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ 0, XF86XK_AudioMute, spawn, {.v = mutecmd } },
	{ 0, XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
	{ 0, XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },
	{ 0, XF86XK_MonBrightnessUp, spawn, {.v = brupcmd} },
	{ 0, XF86XK_MonBrightnessDown, spawn, {.v = brdowncmd} },
	{ 0, XF86XK_AudioNext, spawn, {.v = nextcmd} },
	{ 0, XF86XK_AudioPrev, spawn, {.v = prevcmd} },
	{ 0, XF86XK_AudioPlay, spawn, {.v = playcmd} },
};


/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};