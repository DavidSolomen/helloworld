import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ListIterator;
import java.util.Vector;


public class Example {
	Pcb p;
	Vector<Pcb> v;
	Tu t;
	public Example(Tu t){
		this.t = t;
		v = new Vector<Pcb>();
	}
	public Vector<Pcb> vExaple() throws IOException{
		FileInputStream fis = new FileInputStream(new File("Example.txt"));
		InputStreamReader isr = new InputStreamReader(fis);
		BufferedReader br = new BufferedReader(isr);
		ListIterator<Pcb> li = v.listIterator();
		int count = 0;
		while(true){
			count++;
			if(count==1){
				br.readLine();
			}
			else{
				String s = br.readLine();
				if(s!=null){
					String [] snew = s.split("\\s{1,}");
					p = new Pcb(t,0);
					p.setPID(snew[0]);
					p.setsup(Integer.parseInt(snew[1]));
					p.setrtime(Integer.parseInt(snew[2]));
					p.setares(Integer.parseInt(snew[3]));
					p.setrstore(Integer.parseInt(snew[4]));
					p.sethres(0);
					p.setres(p.getares()-p.gethres());
					p.setRequest(0);
					p.sethtime(0);
					p.setstoreadd(0);
					li.add(p);
				}
				else
					break;
			}
		}
		br.close();
		return v;
	}
}
