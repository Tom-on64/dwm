/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 8;       /* snap pixel */
static const unsigned int gappih    = 8;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 8;       /* vert inner gap between windows */
static const unsigned int gappoh    = 8;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 8;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "BigBlueTermPlus Nerd Font:8" };
static const char dmenufont[]       = "BigBlueTermPlus Nerd Font:8";
static unsigned int baralpha        = 0x40;
static unsigned int borderalpha     = OPAQUE;

/* Default color scheme */
static char normfgcolor[]           = "#bc636a";
static char normbgcolor[]           = "#1f1a24";
static char normbordercolor[]       = "#1f1a24";
static char selfgcolor[]            = "#777289";
static char selbgcolor[]            = "#190e0b";
static char selbordercolor[]        = "#8c534a";

static const char *colors[][3] = {
	/*
	 * SchemeNorm		Normal windows
	 * SchemeSel		Selected windows
	 * SchemeStatus		Statusbar (right)
	 * SchemeTagsSel	Tagbar selected (left)
	 * SchemeTagsNorm	Tagbar normal (left)
	 * SchemeInfoSel	Infobar selected (middle)
	 * SchemeInfoNorm	Infobar normal (middle)
	 */
	/*		    fg		 bg           border */
	[SchemeNorm]	= { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]	= { selfgcolor,  selbgcolor,  selbordercolor },
	[SchemeStatus]	= { normfgcolor, normbgcolor, NULL },
	[SchemeTagsSel]	= { normfgcolor, normbgcolor, NULL },
	[SchemeTagsNorm]= { selfgcolor,  normbgcolor,  NULL },
	[SchemeInfoSel]	= { normfgcolor, normbgcolor, NULL },
	[SchemeInfoNorm]= { normfgcolor, normbgcolor, NULL },

};

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,       NULL,       1 << 1,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

enum {
	L_FIB = 0, // Default
	L_TILE,
	L_FLOAT,
	L_MONO,
	L_DWIN,

	L_END
};

static const Layout layouts[] = {
	/* id	     symbol      arrange function */
	[L_TILE] = { "[]=",      tile    },
	[L_FLOAT]= { "><>",      NULL    },
	[L_MONO] = { "[M]",      monocle },
	[L_FIB]	 = { "[@]",      spiral  },
	[L_DWIN] = { "[\\]",     dwindle },

	[L_END]  = { NULL,       NULL    }
};

/* key definitions */
#define MODKEY Mod4Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 0 } }, /*\
		I have no clue what these do
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },
*/

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[]		= { "dmenu-run", NULL };
static const char *xdgmenucmd[]		= { "dmenu-xdg", NULL };
static const char *powermenucmd[]	= { "dmenu-power", NULL };
static const char *termcmd[]		= { "alacritty", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = dmenucmd} },
	{ MODKEY,	                XK_p,      spawn,          {.v = xdgmenucmd} },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd} },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_s,      togglesticky,   {0} },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_u,      incrgaps,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_u,      incrgaps,       {.i = -1 } },
	{ MODKEY,                       XK_i,      incrigaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incrigaps,      {.i = -1 } },
	{ MODKEY,                       XK_o,      incrogaps,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrogaps,      {.i = -1 } },
	{ MODKEY,                       XK_y,      togglegaps,     {0} },
	{ MODKEY|ShiftMask,             XK_y,      defaultgaps,    {0} },
	STACKKEYS(MODKEY, focus)
	STACKKEYS(MODKEY|ShiftMask, push)
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_w,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	/* Layouts */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[L_TILE]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[L_FLOAT]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[L_MONO]} },
	{ MODKEY|ShiftMask,		XK_f,	   setlayout,	   {.v = &layouts[L_FIB]} },
	{ MODKEY,			XK_w,	   setlayout,	   {.v = &layouts[L_DWIN]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },

	/* TODO: WTF do these do??
	{ MODKEY,                       XK_Tab,    view,           {0} }, 
	{ MODKEY,                       XK_a,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_a,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	*/

	/* Tag switching with a Czech keyboard */
	TAGKEYS(XK_plus,   0)
	TAGKEYS(XK_ecaron, 1)
	TAGKEYS(XK_scaron, 2)
	TAGKEYS(XK_ccaron, 3)
	TAGKEYS(XK_rcaron, 4)
	TAGKEYS(XK_zcaron, 5)
	TAGKEYS(XK_yacute, 6)
	TAGKEYS(XK_aacute, 7)
	TAGKEYS(XK_iacute, 8)

	{ MODKEY|ShiftMask,             XK_q,      spawn,          {.v = powermenucmd} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = { // TODO: Figure this stuff out
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[L_FLOAT]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkStatusText,        0,              Button4,        sigstatusbar,   {.i = 4} },
	{ ClkStatusText,        0,              Button5,        sigstatusbar,   {.i = 5} },
	{ ClkStatusText,        ShiftMask,      Button1,        sigstatusbar,   {.i = 6} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

