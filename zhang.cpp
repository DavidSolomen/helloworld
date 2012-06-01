import java.util.Random;

public class Pcb {
	private String PID;
	private String sup;
	private int rtime;			//Ҫ������ʱ��?
	private int htime;			//�Ѿ�����ʱ��??

	private int res;             //������Դ��???
	private int ares;            //��Դ��������,���������?
	private int hres;			//��ռ����Դ
	private int request;			//��ǰ������Դ��

	private int rstore;			//���������С
	private int storeadd;	//������ʼλ��
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
		s = "PID:"+PID+" ���ȼ�:"+sup+" Ҫ������ʱ��:"+rtime
	     +" ��Դ��������:"+ares+" ��ռ����Դ:"+hres+" ����Ҫ��Դ��:"+res
	     +" ��ǰ������:"+request+" ������ʼλ��:"+storeadd;
		return s;

	}
}