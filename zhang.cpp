import java.util.Random;

public class Pcb {
	private String PID;
	private String sup;
	private int rtime;			//要求运行时间?
	private int htime;			//已经运行时间??

	private int res;             //还需资源量???
	private int ares;            //资源需求总量,最大申请量?
	private int hres;			//已占有资源
	private int request;			//当前申请资源量

	private int rstore;			//所需主存大小
	private int storeadd;	//主存起始位置
	private String s;

	Tu t = null;
	Random rd = new Random();
	CheckSafe cs;
	public Pcb(Tu t,int i){
		this.t = t;
	}
	public Pcb(Tu t) {
		this.t = t;
		PID = t.tpid.getText();
		sup = t.tsup.getText();
		rtime = Integer.parseInt(t.trtime.getText());
		ares = Integer.parseInt(t.tares.getText());
		hres = 0;
		res = ares-hres;
		request = 0;
		rstore = Integer.parseInt(t.trs.getText());
		htime = 0;
		storeadd = 0;
	}
	public void setPID(String s){
		this.PID = s;
	}
	public String getPID(){
		return PID;
	}
	public int getsup(){
		return Integer.parseInt(sup);
	}
	public void setsup(int s){
		this.sup = Integer.toString(s);
	}

	public void setrtime(int s){
		this.rtime=s;
	}
	public int getrtime(){
		return rtime;
	}

	public int gethtime(){
		return htime;
	}
	public void sethtime(int s){
		this.htime = s;
	}

	public int getres(){
		return res;
	}
	public void setres(int s){
		this.res = s;
	}

	public int gethres(){
		return hres;
	}
	public void sethres(int s){
		this.hres = s;
	}

	public int getRequest(){
		return request;
	}
	public void setRequest(int i){
		this.request = i;
	}

	public int getares(){
		return ares;
	}
	public void setares(int s){
		this.ares = s;
	}

	public int getrstore(){
		return rstore;
	}
	public void setrstore(int s){
		this.rstore = s;
	}

	public int getstoreadd(){
		return storeadd;
	}
	public void setstoreadd(int s){
		this.storeadd = s;
	}
	public void giveRequest(){
		this.res = ares - hres;
		if(this.rtime<=t.timeslice)
			this.request = res;
		else
			this.request = rd.nextInt(res + 1);
	}
	public boolean haveRequest() {

		this.hres += request;
		this.res -= request;
		if (t.xaRes >= request) {
			t.xaRes -= request;
			cs = new CheckSafe(t);
			if (!cs.test()) {
				t.xaRes += request;
				this.hres -= request;
				this.res += request;
				return false;
			} else
				return true;
		} else {
			this.hres -= request;
			this.res += request;
			return false;
		}
	}

	public String toString(){
		s = "PID:"+PID+" 优先级:"+sup+" 要求运行时间:"+rtime
	     +" 资源需求总量:"+ares+" 已占有资源:"+hres+" 还需要资源量:"+res
	     +" 当前申请量:"+request+" 主存起始位置:"+storeadd;
		return s;

	}
}