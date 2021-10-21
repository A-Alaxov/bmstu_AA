void polygon::draw_line(int x, int y, int max, matrix &buffer)
{
    while (x < max)						//25	
    {
        buffer[y][x] = not buffer[y][x];//26
        x++;							//27
    }
}

void polygon::edges_proc(size_t start, size_t finish, int max, matrix &buffer)
{
    for (size_t i = start; i < finish; i++)			//13
    {
        point beg(edges[i].p1), end(edges[i].p2);	//14

        if (beg.y == end.y)
            continue;

        if (beg.y > end.y)
        {
            int tmp = beg.y;//15
            beg.y = end.y;	//16
            end.y = tmp;	//17

            tmp = beg.x;	//18
            beg.x = end.x;	//19
            end.x = tmp;	//20
        }

        float ctg = (float) (end.x - beg.x) / (end.y - beg.y);	//21

        float x = beg.x;	//22
        int y = beg.y;		//23

        while (y != end.y)	//24
        {
            draw_line(round(x), y, max, buffer);	//25-27
            x += ctg;								//28
            y += 1;									//29
        }
    }
}

void polygon::find_max(int &max) const
{
    max = points[0]->x;		//2
    for (point *p : points)	//3
        if (p->x > max)
            max = p->x;		//4
}

void polygon::find_up(int &up) const
{
    up = points[0]->y;		//5
    for (point *p : points)	//6
        if (p->y > up)
            up = p->y;		//7
}

void polygon::base(QPainter &painter, QColor bg)
{
    int max, up;	//1
    find_max(max);	//2-4
    find_up(up);	//5-7

    auto buffer = vector<vector<bool>>();	//8
    for (int i = 0; i < up; i++) {			//9
        buffer.emplace_back(max);			//10
        for (int j = 0; j < max; j++) {		//11
            buffer[i][j] = false;			//12
        }
    }

    edges_proc(0, edges.size(), max, buffer);	//13-29
    for (int i = 0; i < up; i++) {				//30
        for (int j = 0; j < max; j++) {			//31
            if (buffer[i][j]) {
                painter.setPen(paint_col);		//32
            }
            else {
                painter.setPen(bg);				//33
            }
            painter.drawPoint(j, i);			//34
        }
    }
}
