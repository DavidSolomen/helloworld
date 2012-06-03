import java.awt.Color;
import java.awt.Graphics;
import java.util.Random;


public class PaintStore {
	public void drawStore(Tu t){
		Random r = new Random();
		Graphics g = t.pg.getGraphics();
		int jpheight = t.pg.getHeight();
		int jpwidth = t.pg.getWidth();
		int jpx = t.pg.getX();
		int jpy = t.pg.getY();
		g.setColor(Color.WHITE);
		g.fillRect(jpx, jpy, jpwidth, jpheight);
		for(int i=0;i<t.queue.getvReady().size();i++){
			int add = t.queue.getvReady().get(i).getstoreadd();
			int rstore = t.queue.getvReady().get(i).getrstore();
			int drawx = add*jpheight/100;
			int height = rstore*jpheight/100;
			g.setColor(new Color(r.nextFloat(),r.nextFloat(),r.nextFloat()));
			g.fillRect(jpx, jpy+drawx, jpwidth, height);
			g.setColor(Color.WHITE);
			g.drawString(t.queue.getvReady().get(i).getPID(), jpx+jpwidth/4, (jpy+drawx)+height/3);
		}
		for(int i=0;i<t.queue.getvWait().size();i++){
			int add = t.queue.getvWait().get(i).getstoreadd();
			int rstore = t.queue.getvWait().get(i).getrstore();
			int drawx = add*jpheight/100;
			int height = rstore*jpheight/100;
			g.setColor(new Color(r.nextFloat(),r.nextFloat(),r.nextFloat()));
			g.fillRect(jpx, jpy+drawx, jpwidth, height);
			g.setColor(Color.WHITE);
			g.drawString(t.queue.getvWait().get(i).getPID(), jpx+jpwidth/4, (jpy+drawx)+height/3);
		}
	}
}
