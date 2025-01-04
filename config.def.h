/* See LICENSE file for copyright and license details. */

/* To Bind XF86 keys */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 6;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Meslo LGM Nerd Font:size=13" };
static const char dmenufont[]       = "Meslo LGM Nerd Font:size=13";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/*
  Allow dwm to execute commands from autostart array in your config.h file. And when you exit dwm all processes from autostart array will be killed.
  Commands from array are executed using execvp(). So if you need to execute shell command you need to prefix it with "sh", "-c" (change sh to any shell you like).
 */
static const char *const autostart[] = {
	"dwm-bar", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask /* Set Win Key as modkey */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define HOLDKEY 0xffeb // Windows Key --> To activate bar

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
/* Use bash to spawn shell commands */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *editorcmd[] = {"emacsclient", "--create-frame", "--alternate-editor=''"};
static const char *gtdcmd[]  = { "todoist-electron", NULL };
static const char *screenshotcmd[]  = { "flameshot", "gui", NULL };

static const char *upbrightness[]  = { "brightnessctl", "set", "+10%", NULL };
static const char *downbrightness[]  = { "brightnessctl", "set", "10%-", NULL };

/* TODO: raise volume through command instead of launching pavucontrol */
static const char *volumecontrol[]  = { "pavucontrol", NULL };
static const char *upvolume[]  = { "wpctl","set-volume", "-l", "1.2", "@DEFAULT_AUDIO_SINK@", "10%+", NULL };
static const char *downvolume[]  = { "wpctl","set-volume", "-l", "1.2", "@DEFAULT_AUDIO_SINK@", "10%-", NULL };
static const char *mutevolume[]  = { "wpctl","set-mute", "@DEFAULT_AUDIO_SINK@", "toggle", NULL };


static const Key keys[] = {
	/* modifier                     key        function        argument */
  
    /* Commands */
	{ MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return, spawn,          {.v = editorcmd} },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          {.v = termcmd } },
    { MODKEY,                       XK_t,      spawn,          {.v = gtdcmd} },
    { MODKEY,                       XK_s,      spawn,          {.v = screenshotcmd} },
    { 0,          XF86XK_MonBrightnessUp,      spawn,           {.v = upbrightness} },
    { 0,          XF86XK_MonBrightnessDown,    spawn,           {.v = downbrightness} },
    { 0,          XF86XK_AudioRaiseVolume,     spawn,           {.v = upvolume} },
    { 0,          XF86XK_AudioLowerVolume,     spawn,           {.v = downvolume} },
    { 0,          XF86XK_AudioMute,            spawn,           {.v = mutevolume} },
    
    /* dwm management keys */
	/* { MODKEY,                       XK_b,      togglebar,      {0} }, */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_m,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_comma,  setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_period, setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ControlMask,           XK_f,      togglefloating, {0} },
    { MODKEY,                       XK_f,      togglefullscr,      {0}},
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    /* Monitor management */
	/* { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } }, */
	/* { MODKEY,                       XK_period, focusmon,       {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } }, */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask|ShiftMask,             XK_k,      quit,           {0} },
    /* Uncomment the line below to toggle bar while holding ModKey*/
	{ 0,             HOLDKEY,      holdbar,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
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

