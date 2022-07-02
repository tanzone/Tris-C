import java.util.regex.Pattern;

/**
 * @author Manuel Tanzi
 * 
 * Classe dedicata alle constanti che verranno utilizzate in tutto il programma
 */
class Constants 
{
	public static final String TITLE_MENU = "Menu v. 2.01";
	public static final String TITLE_PLAY = "Game v. 3.21";
	
	public static final String NAME_CPU = "MACHINE";
	
	public static final String LOCALHOST = "localhost";
	
	public static final String ERROR_LAN = "There is an Error !!";
	
	public static final String IPV4_REGEX =
			"^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\." +
			"(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\." +
			"(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\." +
			"(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$";

	public static final Pattern IPV4_PATTERN = Pattern.compile(IPV4_REGEX);
	
	public static final int N_MIN_PORT = 1;
	public static final int N_MAX_PORT = 65535;
	
	
	//GAME CONTROLLER-----------------------------------------------------------------
	public static final String LIGHT_GREEN = "#7def6f";
	public static final String BACKGROUND  = "#3D4956;";
	public static final String TRANSPARENT = "transparent";
	
	//ALGORITHM
	public static final int ERROR = -1;
	public static final int[][] WINS = new int[][]{{ 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 0, 3, 6 }, { 1, 4, 7 }, { 2, 5, 8 }, { 0, 4, 8 }, { 2, 4, 6 }};
	public static final int[]   SIDE = new int[]  { 1, 3, 5, 7 };
	public static final int[]   EDGE = new int[]  { 0, 2, 6, 8 };
	public static final int[][] EDGENEAR = new int[][]{{0,0}, { 0, 2 }, {0,0}, { 0, 6 }, {0,0}, { 2, 8 }, {0,0}, { 6, 8}};
	public static final int     CENTER = 4;
	
	
	///STATS
	
	
	//Constants
}
