
public class Store {
	private int num;
	private int length;
	private int address;
	private boolean use;
	
	public Store(){
	}
	public void setnum(int i){ //内存块号
		this.num = i;
	}
	public int getnum(){
		return num;
	}
	
	public void setlength(int i){
		this.length = i;
	}
	public int getlength(){
		return length;
	}
	
	public void setaddress(int i){ //内存地址
		this.address = i;
	}
	public int getaddress(){
		return address;
	}
	
	public void setuse(boolean b){ //是否被使用
		this.use = b;
	}
	public boolean getuse(){
		return use;
	}
}
