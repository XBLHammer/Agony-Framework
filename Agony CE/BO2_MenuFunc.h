/* Menu Dimensions */
float flOptionH = 20.0f;
float flOptionW = 150.0f;
float flMenuW = 600.0f;
float flBSize = 6.0f;
float flHSize = 16.0f;

/* Menu Location */
float flMenuX = 250.0f;
float flMenuY = 50.0f;

/* Misc */
char *szHeaderFont = "fonts/720/normalFont";
char *szOptionFont = "fonts/720/normalFont";
float flHeaderSize = 0.5;
float flOptionSize = 0.5;
const char *szIniPath = "HDD:\\TamperedCE.ini";

void playerSub(int c) {
	MenuVars.currentMenu = c + 7;
}