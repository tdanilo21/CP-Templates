using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace WinFormsApp1
{
    class ZabranaParkiranja
    {
        #region atributi
        int x, y, a;
        #endregion

        #region konstruktori
        public ZabranaParkiranja(int x, int y, int a)
        {
            if (a < 0) throw new Exception("dimenzija<0!");
            else
            {
                this.x = x;
                this.y = y;
                this.a = a;
            }
        }
        #endregion

        #region metode
        public void Crtaj(Graphics g)
        {
            SolidBrush cetka = new SolidBrush(Color.Blue);
            g.FillEllipse(cetka, x - a / 2, y - a, a, a);
            Pen olovka = new Pen(Color.Black, a / 8);
            g.DrawLine(olovka, x, y, x, y + a);
            int d = (int)(a / (2 * Math.Sqrt(2)));
            olovka.Color = Color.Red;
            g.DrawLine(olovka, x - d, y - a / 2 - d, x + d, y - a / 2 + d);
            g.DrawEllipse(olovka, x - a / 2, y - a, a, a);
        }

        public void PomeriLevo() { x -= 3; }
        public void PomeriDesno() { x += 3; }
        public void Uvecaj() { a += 3; }
        public void Smanji()
        {
            if (a <= 3) throw new Exception("Dimenzija mora > 0!");
            else a -= 3;
        }
        #endregion
    }
}



/********* App ***********/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WinFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        ZabranaParkiranja znak;

        private void Form1_Load(object sender, EventArgs e)
        {
            znak = new ZabranaParkiranja(ClientRectangle.Width / 2, ClientRectangle.Height - 200, 100);
            
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            znak.Crtaj(e.Graphics);
        }
    }
}

