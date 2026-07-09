#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <string>



using namespace sf;
int comic_count=2;
int levels_count=7;

bool cancel=false;

int category=0;
int scroll=0;
int prechoice=0;

int max_step_counter=8;
int step_count=14;
int hitstate=0;
int dmgEnemy=0;
int dmgPlayer=0;
int primary=0;
int secondary=1;
int special=2;
bool wasPressed=false;
bool isReleased=false;
bool wasF11Pressed=false;
bool isF11Released=false;
bool isFullScreen=true;
bool isVictory=false;
int difficulty=0;
int passive=0;
int victory_counter=120;
int guns_count=39;
int map_width=7681;
int map_height=4321;
int types=5;
int game_state=0;
int main_menu=0;
int choice=1;
int game=2;
int armory=3;
int comics=4;
int multiplayer=5;
int stats=6;
bool isArena=false;
int wave=-1;
int max_waves=3;
int gravity=3;
int friction=1;
double PI=3.141592653589793;
double health1;
int projectile_count=50;
int map_count=8;

double prc(double a, double b)
{

    for (double i=a-b; i>0; i=a-b)
    {
        a-=b;
    }
    while (a<0)
    {
        a+=b;
    }
    if (a<b)
    return a;
    else
        return 0.1;
}


double rt(double x, double y)
{
    if (x!=0)
    {
        return atan(y/x);
    }
    else if (y>=0)
    {
        return 90.0/57;
    }
    else
    {
        return -90.0/57;
    }
}

double rotation (double x, double y)
{
    if (x>0&&y>=0)
    {
        return atan(y/x);
    }
    if (x<0&&y>=0)
    {
        return atan (y/x) + PI;
    }
    if (x<0&&y<0)
    {
        return atan (y/x) + PI;
    }
    if (x>0&&y<0)
    {
        return atan (y/x);
    }
    if (x==0)
    {
        if (y>0)
            return (PI/2);
        else
            return (3*PI/2);
    }
}

int round1(float a)
{
    if (a-int(a)>=0.5)
    {
        return int(a)+1;
    }
    else
        return int(a);
}

double random(int max)
{

    if (max>0)
        return (double((rand()%max))-double(max)/2)/57;
    else
        return 0;
}

int sign(float a)
{
    if (a>0)
        return 1;
    else if (a<0)
        return -1;
    else return 0;
}

int sign1(float a)
{
    if (a>=0)
        return 1;
    else
        return -1;
}


class S
{
public:
    SoundBuffer buffer;
    Sound sound;
    void setS(std::string s)
    {
        buffer.loadFromFile(s);
        sound.setBuffer(buffer);
    }
};

class vec
{
public:
    double x=0;
    double y=0;
    vec(double newx, double newy)
    {
        x=newx;
        y=newy;
    }
    vec()
    {
        x=0;
        y=0;
    }
    void setXY(int newx, int newy)
    {
        x=newx;
        y=newy;
    }
    vec operator+(vec v)
    {
        v.x+=x;
        v.y+=y;
        return v;
    }
    vec operator-(vec v)
    {
        v.x-=x;
        v.y-=y;
        return v;
    }
    void operator+=(vec v)
    {
        x+=v.x;
        y+=v.y;
        return;
    }
    void operator-=(vec v)
    {
        x-=v.x;
        y-=v.y;
        return;
    }
    void operator=(vec v)
    {
        x=v.x;
        y=v.y;
        return;
    }
    bool operator==(vec v)
    {
        if (x==v.x&&y==v.y)
        {
            return true;
        }
        else
            return false;
    }
};

class Map
{
public:
    vec pos;
    vec speed;
    int width=0;
    int height=0;
    int twidth=0;
    int theight=0;
    Texture back_texture;
    Sprite back_sprite;
    Texture** texture;
    Sprite** sprite;
    int** M;
    Map()
    {
        width=0;
        height=0;
        twidth=0;
        theight=0;
    }
    Map(int w, int h, std::string path)
    {
        M=new int*[w];
        for (int i=0; i<w; i++)
        {
            M[i]=new int[h];
        }
        for (int i=0; i<w; i++)
        {
            for (int j=0; j<h; j++)
            {
                M[i][j]=0;
            }
        }
        for (int i=0; i<w; i++)
        {
            M[i][0]=1;
            M[i][h-1]=1;
        }
        for (int i=0; i<w; i++)
        {
            M[0][i]=1;
            M[w-1][i]=1;
        }
        width=w;
        height=h;

        if (width%1920==0)
        {
            twidth=width/1920+1;
        }
        else
        {
            twidth=width/1920+2;
        }

        if (height%1080==0)
        {
            theight=height/1080+1;
        }
        else
        {
            theight=height/1080+2;
        }

        texture=new Texture*[twidth];
        sprite=new Sprite*[twidth];
        for (int i=0; i<twidth; i++)
        {
            texture[i]=new Texture[theight];
            sprite[i]=new Sprite[theight];
            for (int j=0; j<theight; j++)
            {
                std::string str="";
                str+=path;
                str+=std::to_string(i);
                str+="-";
                str+=std::to_string(j);
                str+=".png";
                texture[i][j].loadFromFile(str);
                sprite[i][j].setTexture(texture[i][j]);
                sprite[i][j].setTextureRect(IntRect(0, 0, 1920, 1080));
            }
        }
    }
    void create(int w, int h/*, std::string path, std::string back_path*/)
    {
        M=new int*[w];
        for (int i=0; i<w; i++)
        {
            M[i]=new int[h];
        }
        for (int i=0; i<w; i++)
        {
            for (int j=0; j<h; j++)
            {
                M[i][j]=0;
            }
        }
        for (int i=0; i<w; i++)
        {
            M[i][0]=1;
            M[i][h-1]=1;
        }
        for (int i=0; i<h; i++)
        {
            M[0][i]=1;
            M[w-1][i]=1;
        }
        width=w;
        height=h;

        /*if (width%1920==0)
        {
            twidth=width/1920+1;
        }
        else
        {
            twidth=width/1920+2;
        }

        if (height%1080==0)
        {
            theight=height/1080+1;
        }
        else
        {
            theight=height/1080+2;
        }

        texture=new Texture*[twidth];
        sprite=new Sprite*[twidth];
        for (int i=0; i<twidth; i++)
        {
            texture[i]=new Texture[theight];
            sprite[i]=new Sprite[theight];
            for (int j=0; j<theight; j++)
            {
                std::string str="";
                str+=path;
                str+=std::to_string(i);
                str+="-";
                str+=std::to_string(j);
                str+=".png";
                texture[i][j].loadFromFile(str);
                sprite[i][j].setTexture(texture[i][j]);
                sprite[i][j].setTextureRect(IntRect(0, 0, 1920, 1080));
            }
        }
        back_texture.loadFromFile(back_path);
        back_sprite.setTexture(back_texture);*/

        return;
    }
};
class Position
{
public:
    vec pos;
    vec speed;
    void punch(vec newspeed)
    {
        speed+=newspeed;
        return;
    }

    void engine(int head_height, int height, int width, Map mp)
    {
    //speed.y+=gravity;
    bool bumped_x=false;
    bool bumped_y=false;
    double a1=speed.x;
    double b1=speed.y;
    double cosinus=cos(rotation(speed.x, speed.y));
    double sinus=sin(rotation(speed.x, speed.y));

        //std::cout << std::endl;

        while ((sign(speed.x)==sign(a1)&&speed.x!=0)||(sign(speed.y)==sign(b1)&&speed.y!=0))
        {
            //std::cout << position.x << " " << cosinus << std::endl;
            //std::cout << position.speed_x << std::endl;
            //std::cout << position.y << std::endl;
            //std::cout << position.speed_y << std::endl << std::endl;

            for (int i=-head_height; i<=height; i++)
            {
                if (mp.M[round1(pos.x)+(width+1)*sign(speed.x)][round1(pos.y)+i]>0)
                {
                    bumped_x=true;
                    speed.x=0;
                }
            }
            if (sign(speed.x)==sign(a1)&&speed.x!=0)
            {
                if (abs(speed.x)>abs(cosinus))
                {
                    pos.x+=cosinus;
                    speed.x-=cosinus;
                }
                else
                {
                    pos.x+=speed.x;
                    speed.x=0;
                }

            }
            for (int i=-width; i<=width; i++)
            {
                if (speed.y>0&&mp.M[round1(pos.x)+i][round1(pos.y)+height+1]>0)
                {
                    bumped_y=true;
                    speed.y=0;
                }
                else if (speed.y<0&&mp.M[round1(pos.x)+i][round1(pos.y)-head_height-1]>0)
                {
                    bumped_y=true;
                    speed.y=0;
                }
            }
            if (sign(speed.y)==sign(b1)&&speed.y!=0)
            {
                if (abs(speed.y)>abs(sinus))
                {
                    pos.y+=sinus;
                    speed.y-=sinus;
                }
                else
                {
                    pos.y+=speed.y;
                    speed.y=0;
                }

            }
        }
        if (!bumped_x)
            speed.x=a1;
        else
            speed.x=0;
        if (!bumped_y)
            speed.y=b1;
        else
            speed.y=0;
        return;
    }
};
class Animation
{
public:
    //int scale=1;
    double step_length=1;
    double pos=0.1;
    int length=0;
    int f_count=0;
    Texture* texture;
    int height=0;
    int width=0;
    int shift_x=0;
    int shift_y=0;
    Sprite sprite;
    double shift_rotation;
    double shift;
    double* frame_pos;
    Animation()
    {

    }
    void create(int l, int w, int h, int sh_x, int sh_y, double newstep)
    {
        width=w;
        height=h;
        texture=new Texture[l];
        length=l;
        sprite.setTexture(texture[0]);
        sprite.setTextureRect(IntRect(0, 0, width,  height));
        shift_x=sh_x;
        shift_y=sh_y;
        shift=sqrt(shift_x*shift_x+shift_y*shift_y);
        shift_rotation=rotation(-shift_x, shift_y);
        step_length=newstep;
        //std::cout << shift_rotation/PI;
        return;
    }
    void step(double l)
    {
        pos+=l;
        pos=prc(pos, length);
        int temp=int(pos);
        if (temp<length)
        {
            sprite.setTexture(texture[temp]);
        }
        else
        {
            sprite.setTexture(texture[0]);
        }

        sprite.setTextureRect(IntRect(0, 0, width, height));
        return;
    }
    void step1()
    {
        pos+=step_length;
        pos=prc(pos, length);
        int temp=int(pos);
        if (temp<length)
        {
            sprite.setTexture(texture[temp]);
        }
        else
        {
            sprite.setTexture(texture[0]);
        }

        sprite.setTextureRect(IntRect(0, 0, width, height));
        return;
    }
    void setPos(double newpos)
    {
        pos=newpos;
        pos=prc(pos, length);
        int temp=int(pos);
        if (temp<length)
        {
            sprite.setTexture(texture[temp]);
        }
        else
        {
            sprite.setTexture(texture[0]);
        }

        sprite.setTextureRect(IntRect(0, 0, width, height));
        return;
    }
    void setFrame(int frame)
    {
        if (frame<f_count&&frame>=0)
        {
            setPos(frame_pos[frame]);
        }

    }
    void fill_frames(std::string str, int frames)
    {
        for (int i=0; i<length; i++)
        {
            int j=i/frames;
            std::string str1=str;
            str1+=std::to_string(j);
            str1+=".png";
            texture[i].loadFromFile(str1);
        }
        sprite.setTexture(texture[0]);
        return;
    }
    void setPR(int scale, int x, int y, double rotation)
    {
        sprite.setRotation(rotation*57);
        double rot=scale*shift_rotation-rotation;
        //std::cout << rot/PI << std::endl;

            sprite.setPosition(x+shift*cos(rot)*scale, y-shift*sin(rot)*scale);

            //sprite.setPosition(x-shift*cos(rot), y+shift*sin(rot));


        sprite.setScale(scale, 1);
        return;
    }
};
class Button
{
public:

    Texture texture1;
    Texture texture2;
    Sprite sprite;
    vec pos;
    int width;
    int height;
    bool isUnlocked=false;
    Button()
    {
        width=0;
        height=0;
    }
    Button(std::string string1, std::string string2, int x, int y, int w, int h)
    {
        texture1.loadFromFile(string1);
        texture2.loadFromFile(string2);
        sprite.setTexture(texture1);
        sprite.setTextureRect(IntRect(0, 0, w, h));
        width=w;
        height=h;
        sprite.setPosition(x, y);
        pos.setXY(x, y);
    }
    void create(std::string string1, std::string string2, int x, int y, int w, int h)
    {
        texture1.loadFromFile(string1);
        texture2.loadFromFile(string2);
        sprite.setTexture(texture1);
        sprite.setTextureRect(IntRect(0, 0, w, h));
        width=w;
        height=h;
        sprite.setPosition(x, y);
        pos.setXY(x, y);
    }
    void setPosition(int x, int y)
    {
        pos.setXY(x, y);
        sprite.setPosition(x, y);
    }
    void expand()
    {
        sprite.setTexture(texture2);
        sprite.setScale(double(width+20)/width, double(height+20)/height);
        sprite.setPosition(pos.x-10, pos.y-10);
        return;
    }
    void shrink()
    {
        sprite.setTexture(texture1);
        sprite.setScale(1, 1);
        sprite.setPosition(pos.x, pos.y);
        return;
    }
    bool isPointed(Vector2i mousepos)
    {
        if (IntRect(pos.x, pos.y, width, height).contains(mousepos))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Slot
{
public:
    //bool isWeapon=false;
    bool full=false;
    int holding=0;
    Texture texture;
    Sprite sprite;
    Button button;
    void equip(bool f, int h)
    {
        //isWeapon=w;
        full=f;
        holding=h;
    }
};

class Gun
{
public:
    int x=0;
    int y=0;
    int cat=4;
    int self_explosion_knockback=100;
    double self_damage_multiplier=0.5;
    int explosion_knockback=50;
    Texture icon_texture;
    Sprite icon;
    int predelay=0;
    int max_predelay=0;
    //int state=0;
    int knockback=5;
    int self_knockback=0;
    int max_load=1;
    //String name;
    //String temp="";
    Animation left;
    Animation right;
    Animation left_pre;
    Animation right_pre;
    Animation left_reload;
    Animation right_reload;
    Animation left_deploy;
    Animation right_deploy;
    Animation pre;
    Animation blast;
    Animation projectile;
    SoundBuffer exp_buffer;
    Texture bullet_texture;
    Sprite bullet;
    //Texture icon_texture;
    //Sprite icon;
    Animation crosshair;
    Animation animation;
    SoundBuffer buffer;
    Sound sound;
    SoundBuffer reload_buffer;
    Sound reload_sound;
    Animation deploy;
    Animation reload;
    int width=100;
    int height=100;
    int max_delay=20;
    int damage=25;
    int delay=0;
    bool isPistol=true;
    int max_distance=1200;
    double spread=0;
    int pellets=0;
    double pellet_spread=0.05;
    double swiftness=1;
    bool isProjectile=false;
    int radius=25;
    int proj_speed=300;
    int max_projectile_time=5;
    int proj_width=10;
    int proj_length=100;
    int proj_acceleration=0;
    double splash_multiplier=2;
    int max_deploy=10;
    int deploy_counter=0;
    String name="";
    String temp="";


    int max_ammo=12;
    int ammo=0;
    int ammo_used=1;
    int item_ammo=0;
    int max_reload=40;
    int reload_counter=0;
/*
    double* pos_delay;
    double* pos_predelay;
    double* pos_reload;
    double* pos_deploy;*/
    void create(int newmax_predelay, int newmax_delay, int newmax_deploy, int newmax_reload)
    {
        max_delay=newmax_delay;
        max_deploy=newmax_deploy;
        max_predelay=newmax_predelay;
        max_reload=newmax_reload;
        animation.frame_pos=new double[max_delay+1];
        crosshair.frame_pos=new double[max_delay+1];
        pre.frame_pos=new double[max_predelay+1];
        reload.frame_pos=new double[max_reload+1];
        deploy.frame_pos=new double[max_deploy+1];
        left.frame_pos=new double[max_delay+1];
        left_pre.frame_pos=new double[max_predelay+1];
        left_reload.frame_pos=new double[max_reload+1];
        left_deploy.frame_pos=new double[max_deploy+1];
        right.frame_pos=new double[max_delay+1];
        right_pre.frame_pos=new double[max_predelay+1];
        right_reload.frame_pos=new double[max_reload+1];
        right_deploy.frame_pos=new double[max_deploy+1];
        animation.f_count=max_delay+1;
        crosshair.f_count=max_delay+1;
        pre.f_count=max_predelay+1;
        reload.f_count=max_reload+1;
        deploy.f_count=max_deploy+1;
        left.f_count=max_delay+1;
        left_pre.f_count=max_predelay+1;
        left_reload.f_count=max_reload+1;
        left_deploy.f_count=max_deploy+1;
        right.f_count=max_delay+1;
        right_pre.f_count=max_predelay+1;
        right_reload.f_count=max_reload+1;
        right_deploy.f_count=max_deploy+1;
    }
};
class Entity
{
public:
    Animation left;
    Animation right;
    int jump_counter=0;
    int step_counter=0;
    bool step_play=false;
    int shield=0;
    int max_shield=60;
    Sound reload_sound;
    bool reload_play=false;
    int pre=0;
    int reload=0;
    bool isBeaten=false;
    int counter=0;
    vec* spawn=new vec[map_count];
    bool* isSpawned=new bool[map_count];
    int quantity=0;
    int death_counter=0;
    bool isStanding;
    bool wasDead=true;
    Texture idle;
    Texture jump;
    //Hand* hands=new Hand[items_count];
    Slot* slot=new Slot[4];

    Animation left_reload;
    Animation right_reload;
    Animation body;
    Animation head;
    Animation death;
    Texture bullet_texture;
    Sprite bullet;
    //Hand *hands = new Hand[guns_count];
    Position position;
    int health=144;
    int max_health=144;
    int slot_holding=0;
    //int body_frame_counter=0;
    int pos_x=10;
    int pos_y=0;
    int jump_force=60;
    int head_height=41;
    int height=97;
    double tilt=0;
    double tilt_speed=-1;
    int air_strafe_force=1;
    int strafe_force=2;
    int delay=30;
    int max_delay=30;
    int guns_delay=10;
    int max_guns_delay=15;
    int sight_x=1200;
    int sight_y=960;
    int max_speed=20;
    int animation_delay=0;
    int gun_holding=0;
    SoundBuffer weapon_buffer;
    Sound weapon_sound;
    int shots_left=3;
    int max_shots=3;
    int width=20;
    int max_tilt=10;
    //int shield=0;
    //int max_shield=60;
    int phase=0;
    bool play=false;
    int deploy=0;
    int canEquip()
    {
        for (int i=0; i<4; i++)
        {
            if (!slot[i].full)
            {
                return i;
            }
        }
        return -1;
    }
    void unequip (int s)
    {
        slot[s].full=false;
    }
    void equip(int n)
    {
        int i=canEquip();
        if (i>-1)
        {
            slot[i].full=true;
            slot[i].holding=n;
        }
    }
};

class Projectile
{
public:
    int knockback=0;
    double x=0;
    double y=0;
    int damage=0;
    int speed=0;
    double rotation=0;
    int radius=0;
    int distance_left=0;
    int time=0;
    int acceleration=0;
    Animation animation;
    Sound explosion;
    Animation blast;
    int gun=0;
    double multiplier=1;
};


struct Bullet
{
    int damage=0;
    double final_x=0;
    double final_y=0;
    bool hit=false;
    int distance=0;
};







struct Bullets
{
    //int gun=0;
    double length=0;
    double rotation=0;
};

struct Projectiles
{
    double x=0;
    double y=0;
    int damage=0;
    double rotation=0;
    int gun=0;
    int distance_left=0;
    int time=0;
    Animation animation;
    Sound explosion;
    Animation blast;
    bool play=false;
};

struct Wave
{
    Position position[5][10];
    int health[5][10];
};



//100 100 //game




Bullet shoot (double ent_x, double ent_y, int head_height, int height, int width, double angle, double x, double y, int damage, int max_distance, Map mp)
{
    Bullet bullet;
    double sinus=sin(angle);
    double cosinus=cos(angle);

    for (; bullet.distance<max_distance&&mp.M[round1(x)][round1(y)]==0; bullet.distance++)
    {
        if (x>=ent_x-width&&x<=ent_x+width)
        {

            if (y>=ent_y&&y<=ent_y+height)
            {
                bullet.hit=true;
                bullet.damage=damage;
                bullet.final_x=x;
                bullet.final_y=y;
                return bullet;
            }
            else if (y>=ent_y-head_height&&y<=ent_y)
            {
                bullet.hit=true;
                bullet.damage=damage*2;
                bullet.final_x=x;
                bullet.final_y=y;
                return bullet;
            }
        }
        x+=cosinus;
        y+=sinus;
    }
    bullet.final_x=x;
    bullet.final_y=y;
    return bullet;

}

Bullet enemy_shoot (double ent_x, double ent_y, int head_height, int height, int width, double angle, double x, double y, int damage, int max_distance, Map mp)
{
    Bullet bullet;
    double sinus=sin(angle);
    double cosinus=cos(angle);

    for (; bullet.distance<max_distance&&mp.M[round1(x)][round1(y)]==0; bullet.distance++)
    {
        if (x>=ent_x-width&&x<=ent_x+width)
        {
            if (y>=ent_y-head_height&&y<=ent_y)
            {
                bullet.hit=true;
                bullet.damage=damage*2;
                bullet.final_x=x;
                bullet.final_y=y;
                return bullet;
            }
            if (y>=ent_y&&y<=ent_y+height)
            {
                bullet.hit=true;
                bullet.damage=damage;
                bullet.final_x=x;
                bullet.final_y=y;
                return bullet;
            }
        }
        x+=cosinus;
        y+=sinus;
    }
    bullet.final_x=x;
    bullet.final_y=y;
    return bullet;
}




/*Position engine(Position position, int head_height, int height, int width)
{
    position.speed_y+=gravity;
    bool bumped_x=false;
    bool bumped_y=false;
    double a1=position.speed_x;
    double b1=position.speed_y;
    double cosinus=cos(rotation(position.speed_x, position.speed_y));
    double sinus=sin(rotation(position.speed_x, position.speed_y));

        //std::cout << std::endl;

        while ((sign(position.speed_x)==sign(a1)&&position.speed_x!=0)||(sign(position.speed_y)==sign(b1)&&position.speed_y!=0))
        {
            //std::cout << position.x << " " << cosinus << std::endl;
            //std::cout << position.speed_x << std::endl;
            //std::cout << position.y << std::endl;
            //std::cout << position.speed_y << std::endl << std::endl;

            for (int i=-head_height; i<=height; i++)
            {
                if (map0[round1(position.x)+(width+1)*sign(position.speed_x)][round1(position.y)+i]==1)
                {
                    bumped_x=true;
                    position.speed_x=0;
                }
            }
            if (sign(position.speed_x)==sign(a1)&&position.speed_x!=0)
            {
                if (abs(position.speed_x)>abs(cosinus))
                {
                    position.x+=cosinus;
                    position.speed_x-=cosinus;
                }
                else
                {
                    position.x+=position.speed_x;
                    position.speed_x=0;
                }

            }
            for (int i=-width; i<=width; i++)
            {
                if (position.speed_y>0&&map0[round1(position.x)+i][round1(position.y)+height+1]==1)
                {
                    bumped_y=true;
                    position.speed_y=0;
                }
                else if (position.speed_y<0&&map0[round1(position.x)+i][round1(position.y)-head_height-1]==1)
                {
                    bumped_y=true;
                    position.speed_y=0;
                }
            }
            if (sign(position.speed_y)==sign(b1)&&position.speed_y!=0)
            {
                if (abs(position.speed_y)>abs(sinus))
                {
                    position.y+=sinus;
                    position.speed_y-=sinus;
                }
                else
                {
                    position.y+=position.speed_y;
                    position.speed_y=0;
                }

            }
        }
        if (!bumped_x)
            position.speed_x=a1;
        else
            position.speed_x=0;
        if (!bumped_y)
            position.speed_y=b1;
        else
            position.speed_y=0;
        return position;
}
void setmapborders()
{
    for (int i=0; i<7680; i++)
    {
        for (int j=0; j<4320; j++)
        {
            map0[i][j]=0;
        }
    }
    for (int i=0; i<7680; i++)
    {
        map0[i][0]=1;
        map0[i][4319]=1;
    }
    for (int i=0; i<4320; i++)
    {
        map0[0][i]=1;
        map0[7679][i]=1;
    }
}*/

bool canShoot (double x1, double y1, double x2, double y2, int** M)
{
    double sinus=sin(rotation(x2-x1, y2-y1));
    double cosinus=cos(rotation(x2-x1, y2-y1));
    int sign2=sign(x2-x1);
    while (sign2==sign(x2-x1))
    {
        if (M[round1(x1)][round1(y1)])
        {
            return false;
        }
        x1+=cosinus;
        y1+=sinus;
    }
    return true;
}

Bullet damage(double multiplier, double enemy_x, double enemy_y, int width, double enemy_y1, double enemy_y2, double projectile_x, double projectile_y, double radius, int dmg, int** M)
{
    Bullet bullet;
    //int dmg1=0;
    for (double i=enemy_y1; i<enemy_y; i++)
    {
        for (double j=enemy_x-width; j<=enemy_x+width; j++)
        {
            double dmg2=((radius-sqrt((j-projectile_x)*(j-projectile_x)+(i-projectile_y)*(i-projectile_y)))*dmg/radius)*multiplier;
            if (bullet.damage<dmg2&&canShoot(projectile_x, projectile_y, j, i, M))
            {
                bullet.damage=dmg2;
                bullet.final_x=j-projectile_x;
                bullet.final_y=i-projectile_y;
            }
        }


    }

    for (double i=enemy_y; i<=enemy_y2; i++)
    {
        for (double j=enemy_x-width; j<=enemy_x+width; j++)
        {
            double dmg2=((radius-sqrt((j-projectile_x)*(j-projectile_x)+(i-projectile_y)*(i-projectile_y)))*dmg/radius);
            if (bullet.damage<dmg2&&canShoot(projectile_x, projectile_y, j, i, M))
            {
                bullet.damage=dmg2;
                bullet.final_x=j-projectile_x;
                bullet.final_y=i-projectile_y;
            }
        }


    }
    if ((bullet.final_y<2&&bullet.final_y>-2)&&(bullet.final_x<2&&bullet.final_x>-2))
    {
        double rot=rotation(enemy_x-projectile_x, enemy_y-projectile_y);
        bullet.final_x=cos(rot);
        bullet.final_y=sin(rot);

    }
    return bullet;
}

int main()
{
std::cout << "Starting The Guns...";

//player.gun_holding=
String t;

Font f;
f.loadFromFile("Textures/font.ttf");

Music hitsound;
hitsound.openFromFile("Sounds/effects/hit.wav");

Music killsound;
killsound.openFromFile("Sounds/effects/kill.wav");

Button equip;
equip.create("Textures/equip.png", "Textures/equip.png", 1620, 800, 200, 50);

Texture equipped_texture;
equipped_texture.loadFromFile("Textures/equipped.png");

Sprite equipped;
equipped.setTexture(equipped_texture);
equipped.setPosition(1620, 800);

Button primary_button;
Button secondary_button;
Button special_button;
Button passive_button;


primary_button.create("Textures/0.png", "Textures/0.png", 100, 100, 100, 100);
secondary_button.create("Textures/0.png", "Textures/0.png", 100, 300, 100, 100);
special_button.create("Textures/0.png", "Textures/0.png", 100, 500, 100, 100);
passive_button.create("Textures/0.png", "Textures/0.png", 100, 700, 100, 100);

Text t1("", f, 25);
t1.setColor(Color(0, 127, 0));
t1.setStyle(Text::Regular);
    Music music;
music.setLoop(true);
music.openFromFile("Sounds/music/menu.wav");
music.play();
Map* level=new Map[levels_count];
level[0].create(map_width, map_height);
level[1].create(map_width, map_height);
level[2].create(map_width, map_height);
level[3].create(map_width, map_height);
level[4].create(map_width, map_height);
level[5].create(map_width, map_height);
level[6].create(map_width, map_height);
Map shooting_range_map;
shooting_range_map.create(7681, 4321);
Map arena_map;
Map multiplayer_map;
arena_map.create(7681, 4321);
multiplayer_map.create(map_width, map_height);

for (int i=0; i<96; i++)
                {
                    arena_map.M[i][2176]=1;
                    arena_map.M[7680-i][2176]=1;
                }

                for (int i=400; i<1600; i++)
                {
                    arena_map.M[i][2176]=1;
                    arena_map.M[7680-i][2176]=1;
                }


                for (int i=0; i<400; i++)
                {


                    arena_map.M[i][3916]=1;
                    arena_map.M[7680-i][3916]=1;
                    arena_map.M[i][3056]=1;
                    arena_map.M[7680-i][3056]=1;
                }


                for (int i=2176; i<3064; i++)
                {
                    arena_map.M[800][i]=1;
                    arena_map.M[6880][i]=1;
                }
                for (int i=3400; i<3916; i++)
                {
                    arena_map.M[800][i]=1;
                    arena_map.M[6880][i]=1;
                }

                for (int i=4140; i<4320; i++)
                {
                    arena_map.M[800][i]=1;
                    arena_map.M[6880][i]=1;
                }


                for (int i=800; i<2400; i++)
                {
                    for (int j=3920; j<3964; j++)
                    {
                        arena_map.M[i][j]=1;
                        arena_map.M[7680-i][j]=1;
                        arena_map.M[i][j+356]=1;
                        arena_map.M[7680-i][j+356]=1;
                    }

                }


                for (int i=200; i<800; i++)
                {
                    arena_map.M[i][2616]=1;
                    arena_map.M[7680-i][2616]=1;
                }
                for (int i=400; i<800; i++)
                {
                    arena_map.M[i][3496]=1;
                    arena_map.M[7680-i][3496]=1;
                }

                for (int i=2004; i<2476; i++)
                {
                    arena_map.M[i][2424]=1;
                }
                for (int i=3104; i<4524; i++)
                {
                    arena_map.M[i][2556]=1;
                }
                for (int i=5108; i<5580; i++)
                {
                    arena_map.M[i][2388]=1;
                }
                for (int i=0; i<160; i++)
                {
                    for (int j=3584; j<3912; j++)
                    {
                        arena_map.M[i][j]=1;
                    }
                }
                for (int i=7480; i<7680; i++)
                {
                    for (int j=3584; j<3912; j++)
                    {
                        arena_map.M[i][j]=1;
                    }
                }
                for (int i=344; i<644; i++)
                {
                    arena_map.M[i][2516]=1;
                }
                for (int i=6948; i<7244; i++)
                {
                    arena_map.M[i][2516]=1;
                }

                for (int i=7432; i<7680; i++)
                {
                    for (int j=4140; j<4320; j++)
                    {
                        arena_map.M[i][j]=1;
                    }
                }
                for (int i=7576; i<7624; i++)
                {
                    for (int j=4112; j<4140; j++)
                    {
                        arena_map.M[i][j]=1;
                    }
                }


                arena_map.M[799][3964]=1;
                arena_map.M[6881][3964]=1;


                for (int i=0; i<96; i++)
                {
                    multiplayer_map.M[i][2176]=1;
                    multiplayer_map.M[7680-i][2176]=1;
                }
                //std::cout << "AAA";

                for (int i=400; i<1600; i++)
                {
                    multiplayer_map.M[i][2176]=1;
                    multiplayer_map.M[7680-i][2176]=1;
                }

                for (int i=0; i<400; i++)
                {


                    multiplayer_map.M[i][3916]=1;
                    multiplayer_map.M[7680-i][3916]=1;
                    multiplayer_map.M[i][3056]=1;
                    multiplayer_map.M[7680-i][3056]=1;
                }

                for (int i=2176; i<3064; i++)
                {
                    multiplayer_map.M[800][i]=1;
                    multiplayer_map.M[6880][i]=1;
                }
                for (int i=3400; i<3916; i++)
                {
                    multiplayer_map.M[800][i]=1;
                    multiplayer_map.M[6880][i]=1;
                }

                for (int i=4140; i<4320; i++)
                {
                    multiplayer_map.M[800][i]=1;
                    multiplayer_map.M[6880][i]=1;
                }

                for (int i=800; i<2400; i++)
                {
                    for (int j=3920; j<3964; j++)
                    {
                        multiplayer_map.M[i][j]=1;
                        multiplayer_map.M[7680-i][j]=1;
                        multiplayer_map.M[i][j+356]=1;
                        multiplayer_map.M[7680-i][j+356]=1;
                    }

                }

                for (int i=200; i<800; i++)
                {
                    multiplayer_map.M[i][2616]=1;
                    multiplayer_map.M[7680-i][2616]=1;
                }
                for (int i=400; i<800; i++)
                {
                    multiplayer_map.M[i][3496]=1;
                    multiplayer_map.M[7680-i][3496]=1;
                }

                for (int i=2004; i<2476; i++)
                {
                    multiplayer_map.M[i][2424]=1;
                }
                for (int i=3104; i<4524; i++)
                {
                    multiplayer_map.M[i][2556]=1;
                }
                for (int i=5108; i<5580; i++)
                {
                    multiplayer_map.M[i][2388]=1;
                }
                for (int i=0; i<160; i++)
                {
                    for (int j=3584; j<3912; j++)
                    {
                        multiplayer_map.M[i][j]=1;
                    }
                }
                for (int i=7480; i<7680; i++)
                {
                    for (int j=3584; j<3912; j++)
                    {
                        multiplayer_map.M[i][j]=1;
                    }
                }
                for (int i=344; i<644; i++)
                {
                    multiplayer_map.M[i][2516]=1;
                }
                for (int i=6948; i<7244; i++)
                {
                    multiplayer_map.M[i][2516]=1;
                }

                for (int i=7432; i<7680; i++)
                {
                    for (int j=4140; j<4320; j++)
                    {
                        multiplayer_map.M[i][j]=1;
                    }
                }
                for (int i=7576; i<7624; i++)
                {
                    for (int j=4112; j<4140; j++)
                    {
                        multiplayer_map.M[i][j]=1;
                    }
                }

                multiplayer_map.M[799][3964]=1;
                multiplayer_map.M[6881][3964]=1;


                for (int i=4120; i<4320; i++)
                {
                    shooting_range_map.M[960][i]=1;
                    shooting_range_map.M[1920][i]=1;
                    shooting_range_map.M[2880][i]=1;
                    shooting_range_map.M[4800][i]=1;
                    shooting_range_map.M[5760][i]=1;
                    shooting_range_map.M[6720][i]=1;

                }
                for (int i=3360; i<4320; i++)
                {
                    shooting_range_map.M[i][4000]=1;
                }


                for (int i=0; i<428; i++)
    {
        level[0].M[i][4080]=1;
    }
    for (int i=1112; i<1500; i++)
    {
        for (int j=4196; j<4320; j++)
        {
            level[0].M[i][j]=1;
        }
    }
    for (int i=1256; i<1392; i++)
    {
        for (int j=4120; j<4196; j++)
        {
            level[0].M[i][j]=1;
        }
    }
    for (int i=2760; i<2880; i++)
    {
        for (int j=4076; j<4320; j++)
        {
            level[0].M[i][j]=1;
        }
    }
    for (int i=3444; i<3564; i++)
    {
        for (int j=4076; j<4320; j++)
        {
            level[0].M[i][j]=1;
        }
    }

    for (int i=600; i<1000; i++)
    {
        for (int j=3952; j<4320; j++)
        {
            level[1].M[7680-i][j]=1;
            level[1].M[i][j]=1;
        }
    }


     for (int i=2880; i<3280; i++)
                {
                    level[2].M[i][3960]=1;
                    level[2].M[7680-i][3960]=1;
                }
                for (int i=3520; i<4160; i++)
                {
                    level[2].M[i][3600]=1;
                }


                for (int i=400; i<800; i++)
            {
                level[3].M[i][4000]=1;
            }
            for (int i=0; i<4000; i++)
            {
                level[3].M[400][i]=1;
            }
            for (int i=800; i<1200; i++)
            {
                level[3].M[i][3680]=1;
            }
            for (int i=3680; i<4320; i++)
            {
                level[3].M[1000][i]=1;
            }
            for (int i=1600; i<2400; i++)
            {
                level[3].M[i][3400]=1;
            }
            for (int i=1000; i<1400; i++)
            {
                level[3].M[i][4000]=1;
            }
            for (int i=3040; i<3400; i++)
            {
                level[3].M[2400][i]=1;
            }
            for (int i=2400; i<2800; i++)
            {
                level[3].M[i][3220]=1;
            }
            for (int i=3840; i<4320; i++)
            {
                level[3].M[3840][i]=1;
            }


            for (int i=0; i<400; i++)
                {
                    level[4].M[i][3600]=1;
                }
                for (int i=0; i<4000; i++)
                {
                    level[4].M[800][i]=1;
                }
                for (int i=800; i<1200; i++)
                {
                    level[4].M[i][3360]=1;
                    level[4].M[i][4000]=1;
                }
                for (int i=3040; i<4320; i++)
                {
                    level[4].M[1400][i]=1;
                }
                for (int i=2720; i<4320; i++)
                {
                    level[4].M[3000][i]=1;
                }
                for (int i=1000; i<1600; i++)
                {
                    level[4].M[i][3680]=1;
                }
                for (int i=1400; i<1600; i++)
                {
                    level[4].M[i][4000]=1;
                }
                for (int i=1600; i<2200; i++)
                {
                    level[4].M[i][3360]=1;
                }
                for (int i=2200; i<2800; i++)
                {
                    level[4].M[i][3040]=1;
                }
                for (int i=3200; i<3800; i++)
                {
                    level[4].M[i][2720]=1;
                }
                for (int i=3800; i<4400; i++)
                {
                    level[4].M[i][2400]=1;
                }
                for (int i=3000; i<3200; i++)
                {
                    level[4].M[i][3040]=1;
                    level[4].M[i][3360]=1;
                    level[4].M[i][3680]=1;
                    level[4].M[i][4000]=1;
                }


                for (int i=0; i<3520; i++)
                {
                    level[5].M[7200][i]=1;
                }
                for (int i=4080; i<4320; i++)
                {
                    level[5].M[3840][i]=1;
                }
                for (int i=7200; i<7440; i++)
                {
                    level[5].M[i][3520]=1;
                    level[5].M[i][2720]=1;
                    level[5].M[i][1920]=1;
                    level[5].M[i][1120]=1;
                }
                for (int i=7440; i<7680; i++)
                {
                    level[5].M[i][3920]=1;
                    level[5].M[i][3120]=1;
                    level[5].M[i][2320]=1;
                    level[5].M[i][1520]=1;
                    level[5].M[i][720]=1;
                }

                for (int i=0; i<3920; i++)
                {
                    level[6].M[2880][i]=1;
                    level[6].M[4800][i]=1;
                }

                for (int i=2880; i<3680; i++)
                {
                    level[6].M[i][3920]=1;
                    level[6].M[i][3120]=1;
                    level[6].M[i][2320]=1;
                    level[6].M[i][1520]=1;
                    level[6].M[i][720]=1;
                }
                for (int i=4000; i<4800; i++)
                {
                    level[6].M[i][3920]=1;
                    level[6].M[i][3120]=1;
                    level[6].M[i][2320]=1;
                    level[6].M[i][1520]=1;
                    level[6].M[i][720]=1;
                }
                for (int i=3440; i<4240; i++)
                {
                    level[6].M[i][3520]=1;
                    level[6].M[i][2720]=1;
                    level[6].M[i][1920]=1;
                    level[6].M[i][1120]=1;

                }


    Map mp;



    srand(time(0));

    Font font;
    font.loadFromFile("Textures/font.ttf");

    Text text("", font, 20);
    text.setColor(Color(0, 127, 0));
    text.setStyle(Text::Regular);
    text.setPosition(1620, 600);

    Gun* guns=new Gun[guns_count];

    S *step=new S[14];
    Entity player;
    Entity** enemy=new Entity*[types];
    enemy[0]=new Entity[10];
    enemy[1]=new Entity[10];
    enemy[2]=new Entity[1];
    enemy[3]=new Entity[10];
    enemy[4]=new Entity[1];

    enemy[0][0].quantity=10;
    enemy[1][0].quantity=10;
    enemy[2][0].quantity=1;
    enemy[3][0].quantity=10;
    enemy[4][0].quantity=1;

    Entity enemy_player;
    Position kb;
    Position player_kb;
    Projectile projectile[50];
    Wave *waves = new Wave[max_waves];

//hitsound
    Bullets bullets[10];
    Bullets enemy_bullets[10];

    Projectiles projectiles[50];
    Projectiles enemy_projectiles[50];


    Position spawn[6];

    spawn[0].pos.x=800;
    spawn[0].pos.y=1760;

    spawn[1].pos.x=6880;
    spawn[1].pos.y=1760;

    spawn[2].pos.x=300;
    spawn[2].pos.y=3520;

    spawn[3].pos.x=7380;
    spawn[3].pos.y=3520;

    spawn[4].pos.x=1600;
    spawn[4].pos.y=3520;

    spawn[5].pos.x=6080;
    spawn[5].pos.y=3520;


    //Projectiles projectiles;
    //Projectiles enemy_projectiles;

    //Bullets enemy_bullets;
    //Bullets bullets;

    //Sprite bullet_sprite[10];


    guns[0].isPistol=false;
    guns[1].isPistol=true;
    guns[2].isPistol=false;
    guns[3].isPistol=false;
    guns[4].isPistol=false;
    guns[5].isPistol=true;
    guns[6].isPistol=true;
    guns[7].isPistol=false;
    guns[8].isPistol=false;
    guns[9].isPistol=true;
    guns[10].isPistol=false;
    guns[11].isPistol=false;
    guns[12].isPistol=false;
    guns[13].isPistol=true;
    guns[14].isPistol=false;
    guns[15].isPistol=true;
    guns[16].isPistol=false;
    guns[17].isPistol=false;
    guns[18].isPistol=false;
    guns[19].isPistol=true;
    guns[20].isPistol=false;
    guns[21].isPistol=false;
    guns[22].isPistol=true;
    guns[23].isPistol=false;
    guns[24].isPistol=false;
    guns[25].isPistol=false;
    guns[26].isPistol=true;
    guns[27].isPistol=true;
    guns[28].isPistol=true;
    guns[29].isPistol=false;
    guns[30].isPistol=false;
    guns[31].isPistol=false;
    guns[32].isPistol=false;
    guns[33].isPistol=false;
    guns[34].isPistol=true;
    guns[35].isPistol=false;

    guns[1].swiftness=1.1;
    guns[2].swiftness=0.9;
    guns[4].swiftness=0.95;
    guns[5].swiftness=1.05;
    guns[6].swiftness=1.05;
    guns[7].swiftness=1.05;
    guns[8].swiftness=0.9;
    guns[9].swiftness=1.1;
    guns[10].swiftness=1.05;
    guns[13].swiftness=0.9;
    guns[14].swiftness=0.9;
    guns[15].swiftness=1.05;
    guns[17].swiftness=0.95;
    guns[18].swiftness=0.9;
    guns[22].swiftness=1.15;
    guns[25].swiftness=1.05;
    guns[26].swiftness=1.05;
    guns[28].swiftness=1.05;
    guns[29].swiftness=1.25;
    guns[30].swiftness=0.95;
    guns[31].swiftness=0.9;
    guns[33].swiftness=0.9;
    guns[34].swiftness=1.15;
    guns[35].swiftness=1;

    guns[13].isProjectile=true;

    guns[14].isProjectile=true;
    guns[14].radius=100;
    guns[14].proj_speed=75;

    guns[15].isProjectile=true;
    guns[15].radius=25;
    guns[15].proj_speed=100;

    guns[16].isProjectile=true;
    guns[16].radius=25;
    guns[16].proj_speed=100;

    guns[17].isProjectile=true;
    guns[17].radius=25;
    guns[17].proj_speed=50;
    guns[17].proj_acceleration=-2;
    guns[17].spread=16;
    guns[17].max_distance=620;

    guns[25].isProjectile=true;
    guns[25].radius=25;
    guns[25].proj_speed=75;
    guns[25].spread=10;
    guns[25].max_distance=300;

    guns[21].pellets=2;
    guns[21].pellet_spread=0.015;

    guns[35].pellets=2;
    guns[35].pellet_spread=0.01;

    guns[30].pellets=2;
    guns[30].pellet_spread=0.025;

    guns[28].pellets=2;
    guns[28].pellet_spread=0.015;

    guns[12].pellets=2;
    guns[12].pellet_spread=0.015;

    guns[2].spread=8;
    guns[11].pellet_spread=0.03;

    guns[10].pellets=2;
    guns[11].pellets=2;

    guns[31].isProjectile=true;
    guns[31].radius=200;
    guns[31].proj_speed=75;



    guns[29].spread=5;

    guns[34].max_distance=120;

    /*for (int i=0; i<241; i++)
    {
        for (int j=0; j<guns_count; j++)
        {
            guns[j].crosshair_positionx[i]=0;
            guns[j].positionx[i]=0;
            guns[j].left_positionx[i]=0;
            guns[j].right_positionx[i]=0;
        }
    }*/

    guns[0].name="Machine Gun";
    guns[0].cat=0;
    guns[0].x=300;
    guns[0].y=100;
    guns[0].icon_texture.loadFromFile("Textures/guns/0/icon0.png");
    guns[0].icon.setTexture(guns[0].icon_texture);
    guns[0].damage=24;
    guns[0].spread=2;
    guns[0].create(1, 12, 15, 52);
    guns[0].max_load=25;
    guns[0].max_ammo=25;
    guns[0].isPistol=false;
    guns[0].pre.create(1, 200, 200, 100, 100, 1);
    guns[0].pre.fill_frames("Textures/guns/0/gun", 1);
    guns[0].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[0].left_pre.fill_frames("Textures/guns/0/left", 1);
    guns[0].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[0].right_pre.fill_frames("Textures/guns/0/right", 1);
    guns[0].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[0].animation.fill_frames("Textures/guns/0/gun", 1);
    guns[0].left.create(2, 100, 100, 50, 50, 0.1);
    guns[0].left.fill_frames("Textures/guns/0/left", 1);
    guns[0].right.create(2, 100, 100, 50, 50, 0.1);
    guns[0].right.fill_frames("Textures/guns/0/right", 1);
    guns[0].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[0].reload.fill_frames("Textures/guns/0/reload", 1);
    guns[0].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[0].left_reload.fill_frames("Textures/guns/0/left", 1);
    guns[0].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[0].right_reload.fill_frames("Textures/guns/0/right_reload", 1);
    guns[0].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[0].crosshair.fill_frames("Textures/guns/0/crosshair", 1);


    for (int i=0; i<7; i++)
    {
        guns[0].animation.frame_pos[i]=0.5;
        guns[0].left.frame_pos[i]=0.5;
        guns[0].right.frame_pos[i]=0.5;
        guns[0].crosshair.frame_pos[i]=0.5;
    }
    for (int i=7; i<13; i++)
    {//setFrame
        guns[0].animation.frame_pos[i]=1.5;
        guns[0].left.frame_pos[i]=1.5;
        guns[0].right.frame_pos[i]=1.5;
        guns[0].crosshair.frame_pos[i]=1.5;
    }

    guns[0].pre.frame_pos[0]=0.1;
    guns[0].left_pre.frame_pos[0]=0.1;
    guns[0].right_pre.frame_pos[0]=0.1;


    guns[0].pre.frame_pos[1]=0.1;
    guns[0].left_pre.frame_pos[1]=0.1;
    guns[0].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<6; i++)
    {
        guns[0].reload.frame_pos[i]=0.1;
        guns[0].left_reload.frame_pos[i]=0.1;
        guns[0].right_reload.frame_pos[i]=3.1;
    }
    for (int i=6; i<12; i++)
    {
        guns[0].reload.frame_pos[i]=0.1;
        guns[0].left_reload.frame_pos[i]=0.1;
        guns[0].right_reload.frame_pos[i]=4.1;
    }
    for (int i=12; i<18; i++)
    {
        guns[0].reload.frame_pos[i]=0.1;
        guns[0].left_reload.frame_pos[i]=0.1;
        guns[0].right_reload.frame_pos[i]=3.1;
    }
    for (int i=18; i<26; i++)
    {
        guns[0].reload.frame_pos[i]=0.1;
        guns[0].left_reload.frame_pos[i]=0.1;
        guns[0].right_reload.frame_pos[i]=0.1;
    }
    for (int i=26; i<32; i++)
    {
        guns[0].reload.frame_pos[i]=1.1;
        guns[0].left_reload.frame_pos[i]=0.1;
        guns[0].right_reload.frame_pos[i]=1.1;
    }
    for (int i=32; i<40; i++)
    {
        guns[0].reload.frame_pos[i]=2.1;
        guns[0].left_reload.frame_pos[i]=0.1;
        guns[0].right_reload.frame_pos[i]=2.1;
    }
    for (int i=40; i<46; i++)
    {
        guns[0].reload.frame_pos[i]=1.1;
        guns[0].left_reload.frame_pos[i]=0.1;
        guns[0].right_reload.frame_pos[i]=1.1;
    }
    for (int i=46; i<53; i++)
    {
        guns[0].reload.frame_pos[i]=0.1;
        guns[0].left_reload.frame_pos[i]=0.1;
        guns[0].right_reload.frame_pos[i]=0.1;
    }

    guns[0].buffer.loadFromFile("Sounds/guns/0/0.wav");
    guns[0].sound.setBuffer(guns[0].buffer);

    guns[0].reload_buffer.loadFromFile("Sounds/guns/0/reload0.wav");
    guns[0].reload_sound.setBuffer(guns[0].reload_buffer);

    guns[0].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[0].bullet.setTexture(guns[0].bullet_texture);
    guns[0].bullet.setTextureRect(IntRect(0, 0, 1, 2));








    guns[1].name="Pistol";
    guns[1].cat=1;
    guns[1].x=300;
    guns[1].y=100;
    guns[1].icon_texture.loadFromFile("Textures/guns/1/icon0.png");
    guns[1].icon.setTexture(guns[1].icon_texture);
    guns[1].damage=40;
    guns[1].spread=0;
    guns[1].create(1, 20, 10, 40);
    guns[1].max_load=12;
    guns[1].max_ammo=12;
    guns[1].isPistol=true;
    guns[1].pre.create(1, 200, 200, 100, 100, 1);
    guns[1].pre.fill_frames("Textures/guns/1/gun", 1);
    guns[1].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[1].left_pre.fill_frames("Textures/guns/1/left", 1);
    guns[1].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[1].right_pre.fill_frames("Textures/guns/1/right", 1);
    guns[1].animation.create(3, 200, 200, 100, 100, 0.1);
    guns[1].animation.fill_frames("Textures/guns/1/gun", 1);
    guns[1].left.create(2, 100, 100, 50, 50, 0.1);
    guns[1].left.fill_frames("Textures/guns/1/left", 1);
    guns[1].right.create(1, 100, 100, 50, 50, 0.1);
    guns[1].right.fill_frames("Textures/guns/1/right", 1);
    guns[1].reload.create(2, 200, 200, 100, 100, 0.1);
    guns[1].reload.fill_frames("Textures/guns/1/reload", 1);
    guns[1].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[1].left_reload.fill_frames("Textures/guns/1/left", 1);
    guns[1].right_reload.create(3, 100, 100, 50, 50, 0.1);
    guns[1].right_reload.fill_frames("Textures/guns/1/right_reload", 1);
    guns[1].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[1].crosshair.fill_frames("Textures/guns/1/crosshair", 1);


    for (int i=0; i<5; i++)
    {
        guns[1].animation.frame_pos[i]=0.5;
        guns[1].left.frame_pos[i]=0.5;
        guns[1].right.frame_pos[i]=0.5;
        guns[1].crosshair.frame_pos[i]=0.5;
    }
    for (int i=5; i<12; i++)
    {//setFrame
        guns[1].animation.frame_pos[i]=2.5;
        guns[1].left.frame_pos[i]=0.5;
        guns[1].right.frame_pos[i]=0.5;
        guns[1].crosshair.frame_pos[i]=0.5;
    }

    for (int i=12; i<21; i++)
    {
        guns[1].animation.frame_pos[i]=1.5;
        guns[1].left.frame_pos[i]=1.5;
        guns[1].right.frame_pos[i]=0.5;
        guns[1].crosshair.frame_pos[i]=1.5;
    }

    guns[1].pre.frame_pos[0]=0.1;
    guns[1].left_pre.frame_pos[0]=0.1;
    guns[1].right_pre.frame_pos[0]=0.1;


    guns[1].pre.frame_pos[1]=0.1;
    guns[1].left_pre.frame_pos[1]=0.1;
    guns[1].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<8; i++)
    {
        guns[1].reload.frame_pos[i]=0.1;
        guns[1].left_reload.frame_pos[i]=0.1;
        guns[1].right_reload.frame_pos[i]=0.1;
    }
    for (int i=8; i<16; i++)
    {
        guns[1].reload.frame_pos[i]=1.1;
        guns[1].left_reload.frame_pos[i]=0.1;
        guns[1].right_reload.frame_pos[i]=1.1;
    }
    for (int i=16; i<24; i++)
    {
        guns[1].reload.frame_pos[i]=0.1;
        guns[1].left_reload.frame_pos[i]=0.1;
        guns[1].right_reload.frame_pos[i]=2.1;
    }
    for (int i=24; i<32; i++)
    {
        guns[1].reload.frame_pos[i]=1.1;
        guns[1].left_reload.frame_pos[i]=0.1;
        guns[1].right_reload.frame_pos[i]=1.1;
    }
    for (int i=32; i<41; i++)
    {
        guns[1].reload.frame_pos[i]=0.1;
        guns[1].left_reload.frame_pos[i]=0.1;
        guns[1].right_reload.frame_pos[i]=0.1;
    }


    guns[1].buffer.loadFromFile("Sounds/guns/1/0.wav");
    guns[1].sound.setBuffer(guns[1].buffer);

    guns[1].reload_buffer.loadFromFile("Sounds/guns/1/reload0.wav");
    guns[1].reload_sound.setBuffer(guns[1].reload_buffer);

    guns[1].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[1].bullet.setTexture(guns[1].bullet_texture);
    guns[1].bullet.setTextureRect(IntRect(0, 0, 1, 2));




    guns[2].name="Sandgun";
    guns[2].cat=2;
    guns[2].x=300;
    guns[2].y=100;
    guns[2].knockback=2;
    guns[2].icon_texture.loadFromFile("Textures/guns/2/icon0.png");
    guns[2].icon.setTexture(guns[2].icon_texture);
    guns[2].damage=4;
    guns[2].spread=6;
    guns[2].create(1, 2, 20, 119);
    guns[2].max_load=60;
    guns[2].max_ammo=60;
    guns[2].isPistol=false;
    guns[2].pre.create(1, 200, 200, 100, 100, 1);
    guns[2].pre.fill_frames("Textures/guns/2/gun", 1);
    guns[2].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[2].left_pre.fill_frames("Textures/guns/2/left", 1);
    guns[2].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[2].right_pre.fill_frames("Textures/guns/2/right", 1);
    guns[2].animation.create(1, 200, 200, 100, 100, 0.1);
    guns[2].animation.fill_frames("Textures/guns/2/gun", 1);
    guns[2].left.create(1, 100, 100, 50, 50, 0.1);
    guns[2].left.fill_frames("Textures/guns/2/left", 1);
    guns[2].right.create(1, 100, 100, 50, 50, 0.1);
    guns[2].right.fill_frames("Textures/guns/2/right", 1);
    guns[2].reload.create(4, 200, 200, 100, 100, 0.1);
    guns[2].reload.fill_frames("Textures/guns/2/reload", 1);
    guns[2].left_reload.create(4, 100, 100, 50, 50, 0.1);
    guns[2].left_reload.fill_frames("Textures/guns/2/left_reload", 1);
    guns[2].right_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[2].right_reload.fill_frames("Textures/guns/2/right", 1);
    guns[2].crosshair.create(1, 200, 200, 100, 100, 0.1);
    guns[2].crosshair.fill_frames("Textures/guns/2/crosshair", 1);



        guns[2].animation.frame_pos[0]=0.5;
        guns[2].left.frame_pos[0]=0.5;
        guns[2].right.frame_pos[0]=0.5;
        guns[2].crosshair.frame_pos[0]=0.5;

        guns[2].animation.frame_pos[1]=0.5;
        guns[2].left.frame_pos[1]=0.5;
        guns[2].right.frame_pos[1]=0.5;
        guns[2].crosshair.frame_pos[1]=0.5;


    guns[2].pre.frame_pos[0]=0.1;
    guns[2].left_pre.frame_pos[0]=0.1;
    guns[2].right_pre.frame_pos[0]=0.1;


    guns[2].pre.frame_pos[1]=0.1;
    guns[2].left_pre.frame_pos[1]=0.1;
    guns[2].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<17; i++)
    {
        guns[2].reload.frame_pos[i]=0.1;
        guns[2].left_reload.frame_pos[i]=0.1;
        guns[2].right_reload.frame_pos[i]=0.1;
    }
    for (int i=17; i<34; i++)
    {
        guns[2].reload.frame_pos[i]=1.1;
        guns[2].left_reload.frame_pos[i]=1.1;
        guns[2].right_reload.frame_pos[i]=0.1;
    }
    for (int i=34; i<51; i++)
    {
        guns[2].reload.frame_pos[i]=2.1;
        guns[2].left_reload.frame_pos[i]=2.1;
        guns[2].right_reload.frame_pos[i]=0.1;
    }
    for (int i=51; i<68; i++)
    {
        guns[2].reload.frame_pos[i]=3.1;
        guns[2].left_reload.frame_pos[i]=3.1;
        guns[2].right_reload.frame_pos[i]=0.1;
    }
    for (int i=68; i<85; i++)
    {
        guns[2].reload.frame_pos[i]=2.1;
        guns[2].left_reload.frame_pos[i]=2.1;
        guns[2].right_reload.frame_pos[i]=0.1;
    }
    for (int i=85; i<102; i++)
    {
        guns[2].reload.frame_pos[i]=1.1;
        guns[2].left_reload.frame_pos[i]=1.1;
        guns[2].right_reload.frame_pos[i]=0.1;
    }
    for (int i=102; i<120; i++)
    {
        guns[2].reload.frame_pos[i]=0.1;
        guns[2].left_reload.frame_pos[i]=0.1;
        guns[2].right_reload.frame_pos[i]=0.1;
    }


    guns[2].buffer.loadFromFile("Sounds/guns/2/0.wav");
    guns[2].sound.setBuffer(guns[2].buffer);

    guns[2].reload_buffer.loadFromFile("Sounds/guns/2/reload0.wav");
    guns[2].reload_sound.setBuffer(guns[2].reload_buffer);

    guns[2].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[2].bullet.setTexture(guns[2].bullet_texture);
    guns[2].bullet.setTextureRect(IntRect(0, 0, 1, 2));

    guns[3].name="Lever Action Rifle";
    guns[3].cat=0;
    guns[3].x=450;
    guns[3].y=100;
    guns[3].knockback=6;
    guns[3].icon_texture.loadFromFile("Textures/guns/3/icon0.png");
    guns[3].icon.setTexture(guns[3].icon_texture);
    guns[3].damage=60;
    guns[3].spread=0;
    guns[3].create(1, 40, 10, 56);
    guns[3].max_load=8;
    guns[3].max_ammo=8;
    guns[3].isPistol=false;
    guns[3].pre.create(1, 200, 200, 100, 100, 1);
    guns[3].pre.fill_frames("Textures/guns/3/gun", 1);
    guns[3].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[3].left_pre.fill_frames("Textures/guns/3/left", 1);
    guns[3].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[3].right_pre.fill_frames("Textures/guns/3/right", 1);
    guns[3].animation.create(4, 200, 200, 100, 100, 0.1);
    guns[3].animation.fill_frames("Textures/guns/3/gun", 1);
    guns[3].left.create(3, 100, 100, 50, 50, 0.1);
    guns[3].left.fill_frames("Textures/guns/3/left", 1);
    guns[3].right.create(3, 100, 100, 50, 50, 0.1);
    guns[3].right.fill_frames("Textures/guns/3/right", 1);
    guns[3].reload.create(4, 200, 200, 100, 100, 0.1);
    guns[3].reload.fill_frames("Textures/guns/3/reload", 1);
    guns[3].left_reload.create(2, 100, 100, 50, 50, 0.1);
    guns[3].left_reload.fill_frames("Textures/guns/3/left_reload", 1);
    guns[3].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[3].right_reload.fill_frames("Textures/guns/3/right_reload", 1);
    guns[3].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[3].crosshair.fill_frames("Textures/guns/3/crosshair", 1);



    for (int i=0; i<8; i++)
    {

        guns[3].animation.frame_pos[i]=0.5;
        guns[3].left.frame_pos[i]=0.5;
        guns[3].right.frame_pos[i]=0.5;
        guns[3].crosshair.frame_pos[i]=0.5;
    }
    for (int i=8; i<16; i++)
    {

        guns[3].animation.frame_pos[i]=2.5;
        guns[3].left.frame_pos[i]=0.5;
        guns[3].right.frame_pos[i]=2.5;
        guns[3].crosshair.frame_pos[i]=0.5;
    }
    for (int i=16; i<24; i++)
    {

        guns[3].animation.frame_pos[i]=3.5;
        guns[3].left.frame_pos[i]=2.5;
        guns[3].right.frame_pos[i]=2.5;
        guns[3].crosshair.frame_pos[i]=0.5;
    }
    for (int i=24; i<32; i++)
    {

        guns[3].animation.frame_pos[i]=2.5;
        guns[3].left.frame_pos[i]=0.5;
        guns[3].right.frame_pos[i]=2.5;
        guns[3].crosshair.frame_pos[i]=0.5;
    }
    for (int i=32; i<41; i++)
    {

        guns[3].animation.frame_pos[i]=1.5;
        guns[3].left.frame_pos[i]=1.5;
        guns[3].right.frame_pos[i]=1.5;
        guns[3].crosshair.frame_pos[i]=1.5;
    }





    guns[3].pre.frame_pos[0]=0.1;
    guns[3].left_pre.frame_pos[0]=0.1;
    guns[3].right_pre.frame_pos[0]=0.1;


    guns[3].pre.frame_pos[1]=0.1;
    guns[3].left_pre.frame_pos[1]=0.1;
    guns[3].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<8; i++)
    {
        guns[3].reload.frame_pos[i]=0.1;
        guns[3].left_reload.frame_pos[i]=0.1;
        guns[3].right_reload.frame_pos[i]=4.1;
    }
    for (int i=8; i<16; i++)
    {
        guns[3].reload.frame_pos[i]=3.1;
        guns[3].left_reload.frame_pos[i]=1.1;
        guns[3].right_reload.frame_pos[i]=3.1;
    }
    for (int i=16; i<24; i++)
    {
        guns[3].reload.frame_pos[i]=0.1;
        guns[3].left_reload.frame_pos[i]=0.1;
        guns[3].right_reload.frame_pos[i]=0.1;
    }
    for (int i=24; i<32; i++)
    {
        guns[3].reload.frame_pos[i]=1.1;
        guns[3].left_reload.frame_pos[i]=0.1;
        guns[3].right_reload.frame_pos[i]=1.1;
    }
    for (int i=32; i<40; i++)
    {
        guns[3].reload.frame_pos[i]=2.1;
        guns[3].left_reload.frame_pos[i]=0.1;
        guns[3].right_reload.frame_pos[i]=2.1;
    }
    for (int i=40; i<48; i++)
    {
        guns[3].reload.frame_pos[i]=1.1;
        guns[3].left_reload.frame_pos[i]=0.1;
        guns[3].right_reload.frame_pos[i]=1.1;
    }
    for (int i=48; i<57; i++)
    {
        guns[3].reload.frame_pos[i]=0.1;
        guns[3].left_reload.frame_pos[i]=0.1;
        guns[3].right_reload.frame_pos[i]=0.1;
    }



    guns[3].buffer.loadFromFile("Sounds/guns/3/0.wav");
    guns[3].sound.setBuffer(guns[3].buffer);

    guns[3].reload_buffer.loadFromFile("Sounds/guns/3/reload0.wav");
    guns[3].reload_sound.setBuffer(guns[3].reload_buffer);

    guns[3].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[3].bullet.setTexture(guns[3].bullet_texture);
    guns[3].bullet.setTextureRect(IntRect(0, 0, 1, 2));





    guns[4].name="Laser Rifle";
    guns[4].cat=2;
    guns[4].x=450;
    guns[4].y=100;
    guns[4].knockback=0;
    guns[4].icon_texture.loadFromFile("Textures/guns/4/icon0.png");
    guns[4].icon.setTexture(guns[4].icon_texture);
    guns[4].damage=8;
    guns[4].spread=0;
    guns[4].create(1, 4, 15, 75);
    guns[4].max_load=50;
    guns[4].max_ammo=50;
    guns[4].isPistol=false;
    guns[4].pre.create(1, 200, 200, 100, 100, 1);
    guns[4].pre.fill_frames("Textures/guns/4/gun", 1);
    guns[4].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[4].left_pre.fill_frames("Textures/guns/4/left", 1);
    guns[4].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[4].right_pre.fill_frames("Textures/guns/4/right", 1);
    guns[4].animation.create(1, 200, 200, 100, 100, 0.1);
    guns[4].animation.fill_frames("Textures/guns/4/gun", 1);
    guns[4].left.create(1, 100, 100, 50, 50, 0.1);
    guns[4].left.fill_frames("Textures/guns/4/left", 1);
    guns[4].right.create(1, 100, 100, 50, 50, 0.1);
    guns[4].right.fill_frames("Textures/guns/4/right", 1);
    guns[4].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[4].reload.fill_frames("Textures/guns/4/reload", 1);
    guns[4].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[4].left_reload.fill_frames("Textures/guns/4/left", 1);
    guns[4].right_reload.create(3, 100, 100, 50, 50, 0.1);
    guns[4].right_reload.fill_frames("Textures/guns/4/right_reload", 1);
    guns[4].crosshair.create(1, 200, 200, 100, 100, 0.1);
    guns[4].crosshair.fill_frames("Textures/guns/4/crosshair", 1);



        guns[4].animation.frame_pos[0]=0.5;
        guns[4].left.frame_pos[0]=0.5;
        guns[4].right.frame_pos[0]=0.5;
        guns[4].crosshair.frame_pos[0]=0.5;

        guns[4].animation.frame_pos[1]=0.5;
        guns[4].left.frame_pos[1]=0.5;
        guns[4].right.frame_pos[1]=0.5;
        guns[4].crosshair.frame_pos[1]=0.5;

        guns[4].animation.frame_pos[2]=0.5;
        guns[4].left.frame_pos[2]=0.5;
        guns[4].right.frame_pos[2]=0.5;
        guns[4].crosshair.frame_pos[2]=0.5;

        guns[4].animation.frame_pos[3]=0.5;
        guns[4].left.frame_pos[3]=0.5;
        guns[4].right.frame_pos[3]=0.5;
        guns[4].crosshair.frame_pos[3]=0.5;


    guns[4].pre.frame_pos[0]=0.1;
    guns[4].left_pre.frame_pos[0]=0.1;
    guns[4].right_pre.frame_pos[0]=0.1;


    guns[4].pre.frame_pos[1]=0.1;
    guns[4].left_pre.frame_pos[1]=0.1;
    guns[4].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<15; i++)
    {
        guns[4].reload.frame_pos[i]=0.1;
        guns[4].left_reload.frame_pos[i]=0.1;
        guns[4].right_reload.frame_pos[i]=0.1;
    }
    for (int i=15; i<30; i++)
    {
        guns[4].reload.frame_pos[i]=1.1;
        guns[4].left_reload.frame_pos[i]=0.1;
        guns[4].right_reload.frame_pos[i]=1.1;
    }
    for (int i=30; i<45; i++)
    {
        guns[4].reload.frame_pos[i]=2.1;
        guns[4].left_reload.frame_pos[i]=0.1;
        guns[4].right_reload.frame_pos[i]=2.1;
    }
    for (int i=45; i<60; i++)
    {
        guns[4].reload.frame_pos[i]=1.1;
        guns[4].left_reload.frame_pos[i]=0.1;
        guns[4].right_reload.frame_pos[i]=1.1;
    }
    for (int i=60; i<76; i++)
    {
        guns[4].reload.frame_pos[i]=0.1;
        guns[4].left_reload.frame_pos[i]=0.1;
        guns[4].right_reload.frame_pos[i]=0.1;
    }

    guns[4].buffer.loadFromFile("Sounds/guns/4/0.wav");
    guns[4].sound.setBuffer(guns[4].buffer);

    guns[4].reload_buffer.loadFromFile("Sounds/guns/4/reload0.wav");
    guns[4].reload_sound.setBuffer(guns[4].reload_buffer);

    guns[4].bullet_texture.loadFromFile("Textures/red_laser.png");
    guns[4].bullet.setTexture(guns[4].bullet_texture);
    guns[4].bullet.setTextureRect(IntRect(0, 0, 1, 2));





    guns[5].name="Revolver";
    guns[5].cat=1;
    guns[5].x=450;
    guns[5].y=100;
    guns[5].knockback=6;
    guns[5].icon_texture.loadFromFile("Textures/guns/5/icon0.png");
    guns[5].icon.setTexture(guns[5].icon_texture);
    guns[5].damage=72;
    guns[5].spread=0;
    guns[5].create(1, 60, 5, 82);
    guns[5].max_load=6;
    guns[5].max_ammo=6;
    guns[5].isPistol=true;
    guns[5].pre.create(1, 200, 200, 100, 100, 1);
    guns[5].pre.fill_frames("Textures/guns/5/gun", 1);
    guns[5].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[5].left_pre.fill_frames("Textures/guns/5/left", 1);
    guns[5].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[5].right_pre.fill_frames("Textures/guns/5/right", 1);
    guns[5].animation.create(3, 200, 200, 100, 100, 0.1);
    guns[5].animation.fill_frames("Textures/guns/5/gun", 1);
    guns[5].left.create(2, 100, 100, 50, 50, 0.1);
    guns[5].left.fill_frames("Textures/guns/5/left", 1);
    guns[5].right.create(1, 100, 100, 50, 50, 0.1);
    guns[5].right.fill_frames("Textures/guns/5/right", 1);
    guns[5].reload.create(6, 200, 200, 100, 100, 0.1);
    guns[5].reload.fill_frames("Textures/guns/5/reload", 1);
    guns[5].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[5].left_reload.fill_frames("Textures/guns/5/left", 1);
    guns[5].right_reload.create(3, 100, 100, 50, 50, 0.1);
    guns[5].right_reload.fill_frames("Textures/guns/5/right_reload", 1);
    guns[5].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[5].crosshair.fill_frames("Textures/guns/5/crosshair", 1);
    //std::cout << "Test1";

    for (int i=0; i<12; i++)
    {
        guns[5].animation.frame_pos[i]=0.5;
        guns[5].left.frame_pos[i]=0.5;
        guns[5].right.frame_pos[i]=0.5;
        guns[5].crosshair.frame_pos[i]=0.5;
    }
    for (int i=12; i<24; i++)
    {
        guns[5].animation.frame_pos[i]=2.5;
        guns[5].left.frame_pos[i]=0.5;
        guns[5].right.frame_pos[i]=0.5;
        guns[5].crosshair.frame_pos[i]=0.5;
    }
    for (int i=24; i<61; i++)
    {
        guns[5].animation.frame_pos[i]=1.5;
        guns[5].left.frame_pos[i]=1.5;
        guns[5].right.frame_pos[i]=0.5;
        guns[5].crosshair.frame_pos[i]=1.5;


    }
    //std::cout << "Test2";


    for (int i=0; i<4; i++)
    {
        guns[5].reload.frame_pos[i]=0.5;
        guns[5].left_reload.frame_pos[i]=0.5;
        guns[5].right_reload.frame_pos[i]=0.5;
        //guns[5].crosshair.frame_pos[i]=0.5;
    }
    for (int i=4; i<12; i++)
    {
        guns[5].reload.frame_pos[i]=5.5;
        guns[5].left_reload.frame_pos[i]=0.5;
        guns[5].right_reload.frame_pos[i]=0.5;
        //guns[5].crosshair.frame_pos[i]=0.5;
    }
    for (int i=12; i<16; i++)
    {
        guns[5].reload.frame_pos[i]=0.5;
        guns[5].left_reload.frame_pos[i]=0.5;
        guns[5].right_reload.frame_pos[i]=0.5;
        //guns[1].crosshair.frame_pos[i]=0.5;
    }
    for (int i=16; i<20; i++)
    {
        guns[5].reload.frame_pos[i]=1.5;
        guns[5].left_reload.frame_pos[i]=0.5;
        guns[5].right_reload.frame_pos[i]=0.5;
        //guns[1].crosshair.frame_pos[i]=0.5;
    }
    for (int i=20; i<24; i++)
    {
        guns[5].reload.frame_pos[i]=4.5;
        guns[5].left_reload.frame_pos[i]=0.5;
        guns[5].right_reload.frame_pos[i]=0.5;
        //guns[1].crosshair.frame_pos[i]=0.5;
    }
    for (int i=24; i<28; i++)
    {
        guns[5].reload.frame_pos[i]=3.5;
        guns[5].left_reload.frame_pos[i]=0.5;
        guns[5].right_reload.frame_pos[i]=1.5;
        //guns[1].crosshair.frame_pos[i]=0.5;
    }

    for (int i=28; i<46; i++)
    {
        guns[5].reload.frame_pos[i]=2.5;
        guns[5].left_reload.frame_pos[i]=0.5;
        guns[5].right_reload.frame_pos[i]=2.5;
        //guns[1].crosshair.frame_pos[i]=0.5;
    }
    for (int i=46; i<64; i++)
    {
        guns[5].reload.frame_pos[i]=2.5;
        guns[5].left_reload.frame_pos[i]=0.5;
        guns[5].right_reload.frame_pos[i]=1.5;
        //guns[1].crosshair.frame_pos[i]=0.5;
    }
    for (int i=64; i<83; i++)
    {
        guns[5].reload.frame_pos[i]=1.5;
        guns[5].left_reload.frame_pos[i]=0.5;
        guns[5].right_reload.frame_pos[i]=0.5;
        //guns[1].crosshair.frame_pos[i]=0.5;
    }






    guns[5].pre.frame_pos[0]=0.1;
    guns[5].left_pre.frame_pos[0]=0.1;
    guns[5].right_pre.frame_pos[0]=0.1;


    guns[5].pre.frame_pos[1]=0.1;
    guns[5].left_pre.frame_pos[1]=0.1;
    guns[5].right_pre.frame_pos[1]=0.1;





    guns[5].buffer.loadFromFile("Sounds/guns/5/0.wav");
    guns[5].sound.setBuffer(guns[5].buffer);

    guns[5].reload_buffer.loadFromFile("Sounds/guns/5/reload0.wav");
    guns[5].reload_sound.setBuffer(guns[5].reload_buffer);

    guns[5].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[5].bullet.setTexture(guns[5].bullet_texture);
    guns[5].bullet.setTextureRect(IntRect(0, 0, 1, 2));


    guns[6].name="Nailgun";
    guns[6].cat=1;
    guns[6].x=600;
    guns[6].y=100;
    guns[6].explosion_knockback=0;
    guns[6].self_explosion_knockback=0;
    guns[6].self_damage_multiplier=0;
    guns[6].icon_texture.loadFromFile("Textures/guns/6/icon0.png");
    guns[6].icon.setTexture(guns[6].icon_texture);
    guns[6].damage=25;

    guns[6].spread=0;
    guns[6].create(1, 12, 10, 60);
    guns[6].max_load=20;
    guns[6].max_ammo=20;
    guns[6].isPistol=true;
    guns[6].pre.create(1, 200, 200, 100, 100, 1);
    guns[6].pre.fill_frames("Textures/guns/6/gun", 1);
    guns[6].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[6].left_pre.fill_frames("Textures/guns/6/left", 1);
    guns[6].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[6].right_pre.fill_frames("Textures/guns/6/right", 1);
    guns[6].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[6].animation.fill_frames("Textures/guns/6/gun", 1);
    guns[6].left.create(1, 100, 100, 50, 50, 0.1);
    guns[6].left.fill_frames("Textures/guns/6/left", 1);
    guns[6].right.create(1, 100, 100, 50, 50, 0.1);
    guns[6].right.fill_frames("Textures/guns/6/right", 1);
    guns[6].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[6].reload.fill_frames("Textures/guns/6/reload", 1);
    guns[6].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[6].left_reload.fill_frames("Textures/guns/6/left", 1);
    guns[6].right_reload.create(3, 100, 100, 50, 50, 0.1);
    guns[6].right_reload.fill_frames("Textures/guns/6/right_reload", 1);
    guns[6].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[6].crosshair.fill_frames("Textures/guns/6/crosshair", 1);
    guns[6].isProjectile=true;
    guns[6].projectile.create(1, 40, 10, 40, 5, 0.1);
    guns[6].projectile.fill_frames("Textures/guns/6/projectile", 1);

    guns[6].blast.create(2, 40, 40, 20, 20, 0.15);
    guns[6].blast.fill_frames("Textures/guns/6/blast", 1);

    guns[6].max_projectile_time=10;
    guns[6].blast.frame_pos=new double[11];
    guns[6].blast.f_count=11;
    for (int i=0; i<7; i++)
    {
        guns[6].blast.frame_pos[i]=1.1;
    }
    for (int i=7; i<11; i++)
    {
        guns[6].blast.frame_pos[i]=0.1;
    }

    guns[6].projectile.frame_pos=new double[5];
    guns[6].projectile.f_count=5;
    guns[6].projectile.frame_pos[0]=0.1;
    guns[6].projectile.frame_pos[1]=0.1;
    guns[6].projectile.frame_pos[2]=0.1;
    guns[6].projectile.frame_pos[3]=0.1;
    guns[6].projectile.frame_pos[4]=0.1;

    //guns[6].


    for (int i=0; i<5; i++)
    {
        guns[6].animation.frame_pos[i]=0.5;
        guns[6].left.frame_pos[i]=0.5;
        guns[6].right.frame_pos[i]=0.5;
        guns[6].crosshair.frame_pos[i]=0.5;
    }
    for (int i=5; i<12; i++)
    {//setFrame
        guns[6].animation.frame_pos[i]=1.5;
        guns[6].left.frame_pos[i]=0.5;
        guns[6].right.frame_pos[i]=0.5;
        guns[6].crosshair.frame_pos[i]=1.5;
    }



    guns[6].pre.frame_pos[0]=0.1;
    guns[6].left_pre.frame_pos[0]=0.1;
    guns[6].right_pre.frame_pos[0]=0.1;


    guns[6].pre.frame_pos[1]=0.1;
    guns[6].left_pre.frame_pos[1]=0.1;
    guns[6].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<12; i++)
    {
        guns[6].reload.frame_pos[i]=0.1;
        guns[6].left_reload.frame_pos[i]=0.1;
        guns[6].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[6].reload.frame_pos[i]=1.1;
        guns[6].left_reload.frame_pos[i]=0.1;
        guns[6].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[6].reload.frame_pos[i]=2.1;
        guns[6].left_reload.frame_pos[i]=0.1;
        guns[6].right_reload.frame_pos[i]=2.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[6].reload.frame_pos[i]=1.1;
        guns[6].left_reload.frame_pos[i]=0.1;
        guns[6].right_reload.frame_pos[i]=1.1;
    }
    for (int i=48; i<61; i++)
    {
        guns[6].reload.frame_pos[i]=0.1;
        guns[6].left_reload.frame_pos[i]=0.1;
        guns[6].right_reload.frame_pos[i]=0.1;
    }


    guns[6].buffer.loadFromFile("Sounds/guns/6/0.wav");
    guns[6].sound.setBuffer(guns[6].buffer);

    guns[6].reload_buffer.loadFromFile("Sounds/guns/6/reload0.wav");
    guns[6].reload_sound.setBuffer(guns[6].reload_buffer);

    /*guns[6].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[6].bullet.setTexture(guns[6].bullet_texture);
    guns[6].bullet.setTextureRect(IntRect(0, 0, 1, 2));*/




    guns[7].name="Submachine Gun";
    guns[7].cat=0;
    guns[7].x=600;
    guns[7].y=100;
    guns[7].icon_texture.loadFromFile("Textures/guns/7/icon0.png");
    guns[7].icon.setTexture(guns[7].icon_texture);
    guns[7].damage=20;
    guns[7].spread=2;
    guns[7].create(1, 10, 10, 52);
    guns[7].max_load=40;
    guns[7].max_ammo=40;
    guns[7].isPistol=false;
    guns[7].pre.create(1, 200, 200, 100, 100, 1);
    guns[7].pre.fill_frames("Textures/guns/7/gun", 1);
    guns[7].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[7].left_pre.fill_frames("Textures/guns/7/left", 1);
    guns[7].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[7].right_pre.fill_frames("Textures/guns/7/right", 1);
    guns[7].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[7].animation.fill_frames("Textures/guns/7/gun", 1);
    guns[7].left.create(2, 100, 100, 50, 50, 0.1);
    guns[7].left.fill_frames("Textures/guns/7/left", 1);
    guns[7].right.create(2, 100, 100, 50, 50, 0.1);
    guns[7].right.fill_frames("Textures/guns/7/right", 1);
    guns[7].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[7].reload.fill_frames("Textures/guns/7/reload", 1);
    guns[7].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[7].left_reload.fill_frames("Textures/guns/7/left", 1);
    guns[7].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[7].right_reload.fill_frames("Textures/guns/7/right_reload", 1);
    guns[7].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[7].crosshair.fill_frames("Textures/guns/7/crosshair", 1);


    for (int i=0; i<6; i++)
    {
        guns[7].animation.frame_pos[i]=0.5;
        guns[7].left.frame_pos[i]=0.5;
        guns[7].right.frame_pos[i]=0.5;
        guns[7].crosshair.frame_pos[i]=0.5;
    }
    for (int i=6; i<11; i++)
    {//setFrame
        guns[7].animation.frame_pos[i]=1.5;
        guns[7].left.frame_pos[i]=1.5;
        guns[7].right.frame_pos[i]=1.5;
        guns[7].crosshair.frame_pos[i]=1.5;
    }

    guns[7].pre.frame_pos[0]=0.1;
    guns[7].left_pre.frame_pos[0]=0.1;
    guns[7].right_pre.frame_pos[0]=0.1;


    guns[7].pre.frame_pos[1]=0.1;
    guns[7].left_pre.frame_pos[1]=0.1;
    guns[7].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<6; i++)
    {
        guns[7].reload.frame_pos[i]=0.1;
        guns[7].left_reload.frame_pos[i]=0.1;
        guns[7].right_reload.frame_pos[i]=3.1;
    }
    for (int i=6; i<12; i++)
    {
        guns[7].reload.frame_pos[i]=0.1;
        guns[7].left_reload.frame_pos[i]=0.1;
        guns[7].right_reload.frame_pos[i]=4.1;
    }
    for (int i=12; i<18; i++)
    {
        guns[7].reload.frame_pos[i]=0.1;
        guns[7].left_reload.frame_pos[i]=0.1;
        guns[7].right_reload.frame_pos[i]=3.1;
    }
    for (int i=18; i<26; i++)
    {
        guns[7].reload.frame_pos[i]=0.1;
        guns[7].left_reload.frame_pos[i]=0.1;
        guns[7].right_reload.frame_pos[i]=0.1;
    }
    for (int i=26; i<32; i++)
    {
        guns[7].reload.frame_pos[i]=1.1;
        guns[7].left_reload.frame_pos[i]=0.1;
        guns[7].right_reload.frame_pos[i]=1.1;
    }
    for (int i=32; i<40; i++)
    {
        guns[7].reload.frame_pos[i]=2.1;
        guns[7].left_reload.frame_pos[i]=0.1;
        guns[7].right_reload.frame_pos[i]=2.1;
    }
    for (int i=40; i<46; i++)
    {
        guns[7].reload.frame_pos[i]=1.1;
        guns[7].left_reload.frame_pos[i]=0.1;
        guns[7].right_reload.frame_pos[i]=1.1;
    }
    for (int i=46; i<53; i++)
    {
        guns[7].reload.frame_pos[i]=0.1;
        guns[7].left_reload.frame_pos[i]=0.1;
        guns[7].right_reload.frame_pos[i]=0.1;
    }

    guns[7].buffer.loadFromFile("Sounds/guns/7/0.wav");
    guns[7].sound.setBuffer(guns[7].buffer);

    guns[7].reload_buffer.loadFromFile("Sounds/guns/7/reload0.wav");
    guns[7].reload_sound.setBuffer(guns[7].reload_buffer);

    guns[7].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[7].bullet.setTexture(guns[7].bullet_texture);
    guns[7].bullet.setTextureRect(IntRect(0, 0, 1, 2));

    guns[8].name="Laser Gun";
    guns[8].cat=2;
    guns[8].x=600;
    guns[8].y=100;
    guns[8].knockback=0;
    guns[8].icon_texture.loadFromFile("Textures/guns/8/icon0.png");
    guns[8].icon.setTexture(guns[8].icon_texture);
    guns[8].damage=144;
    guns[8].spread=0;
    guns[8].create(1, 150, 25, 220);
    guns[8].max_load=4;
    guns[8].max_ammo=4;
    guns[8].isPistol=false;
    guns[8].pre.create(1, 200, 200, 100, 100, 1);
    guns[8].pre.fill_frames("Textures/guns/8/gun", 1);
    guns[8].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[8].left_pre.fill_frames("Textures/guns/8/left", 1);
    guns[8].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[8].right_pre.fill_frames("Textures/guns/8/right", 1);
    guns[8].animation.create(3, 200, 200, 100, 100, 0.1);
    guns[8].animation.fill_frames("Textures/guns/8/gun", 1);
    guns[8].left.create(2, 100, 100, 50, 50, 0.1);
    guns[8].left.fill_frames("Textures/guns/8/left", 1);
    guns[8].right.create(2, 100, 100, 50, 50, 0.1);
    guns[8].right.fill_frames("Textures/guns/8/right", 1);
    guns[8].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[8].reload.fill_frames("Textures/guns/8/reload", 1);
    guns[8].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[8].left_reload.fill_frames("Textures/guns/8/left", 1);
    guns[8].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[8].right_reload.fill_frames("Textures/guns/8/right_reload", 1);
    guns[8].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[8].crosshair.fill_frames("Textures/guns/8/crosshair", 1);


    for (int i=0; i<20; i++)
    {
        guns[8].animation.frame_pos[i]=0.5;
        guns[8].left.frame_pos[i]=0.5;
        guns[8].right.frame_pos[i]=0.5;
        guns[8].crosshair.frame_pos[i]=0.5;
    }
    for (int i=20; i<120; i++)
    {//setFrame
        guns[8].animation.frame_pos[i]=2.5;
        guns[8].left.frame_pos[i]=1.5;
        guns[8].right.frame_pos[i]=1.5;
        guns[8].crosshair.frame_pos[i]=0.5;
    }
    for (int i=120; i<151; i++)
    {
        guns[8].animation.frame_pos[i]=1.5;
        guns[8].left.frame_pos[i]=0.5;
        guns[8].right.frame_pos[i]=0.5;
        guns[8].crosshair.frame_pos[i]=1.5;
    }

    guns[8].pre.frame_pos[0]=0.1;
    guns[8].left_pre.frame_pos[0]=0.1;
    guns[8].right_pre.frame_pos[0]=0.1;


    guns[8].pre.frame_pos[1]=0.1;
    guns[8].left_pre.frame_pos[1]=0.1;
    guns[8].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<30; i++)
    {
        guns[8].reload.frame_pos[i]=0.1;
        guns[8].left_reload.frame_pos[i]=0.1;
        guns[8].right_reload.frame_pos[i]=4.1;
    }
    for (int i=30; i<60; i++)
    {
        guns[8].reload.frame_pos[i]=0.1;
        guns[8].left_reload.frame_pos[i]=0.1;
        guns[8].right_reload.frame_pos[i]=3.1;
    }
    for (int i=60; i<100; i++)
    {
        guns[8].reload.frame_pos[i]=0.1;
        guns[8].left_reload.frame_pos[i]=0.1;
        guns[8].right_reload.frame_pos[i]=0.1;
    }
    for (int i=100; i<130; i++)
    {
        guns[8].reload.frame_pos[i]=1.1;
        guns[8].left_reload.frame_pos[i]=0.1;
        guns[8].right_reload.frame_pos[i]=1.1;
    }
    for (int i=130; i<160; i++)
    {
        guns[8].reload.frame_pos[i]=2.1;
        guns[8].left_reload.frame_pos[i]=0.1;
        guns[8].right_reload.frame_pos[i]=2.1;
    }
    for (int i=160; i<190; i++)
    {
        guns[8].reload.frame_pos[i]=1.1;
        guns[8].left_reload.frame_pos[i]=0.1;
        guns[8].right_reload.frame_pos[i]=1.1;
    }
    for (int i=190; i<221; i++)
    {
        guns[8].reload.frame_pos[i]=0.1;
        guns[8].left_reload.frame_pos[i]=0.1;
        guns[8].right_reload.frame_pos[i]=0.1;
    }


    guns[8].buffer.loadFromFile("Sounds/guns/8/0.wav");
    guns[8].sound.setBuffer(guns[8].buffer);

    guns[8].reload_buffer.loadFromFile("Sounds/guns/8/reload0.wav");
    guns[8].reload_sound.setBuffer(guns[8].reload_buffer);

    guns[8].bullet_texture.loadFromFile("Textures/purple_laser.png");
    guns[8].bullet.setTexture(guns[8].bullet_texture);
    guns[8].bullet.setTextureRect(IntRect(0, 0, 1, 2));



    guns[9].name="Uzi";
    guns[9].cat=1;
    guns[9].x=750;
    guns[9].y=100;
    guns[9].knockback=3;
    guns[9].icon_texture.loadFromFile("Textures/guns/9/icon0.png");
    guns[9].icon.setTexture(guns[9].icon_texture);
    guns[9].damage=10;
    guns[9].spread=4;
    guns[9].create(1, 5, 10, 48);
    guns[9].max_load=40;
    guns[9].max_ammo=40;
    guns[9].isPistol=true;
    guns[9].pre.create(1, 200, 200, 100, 100, 1);
    guns[9].pre.fill_frames("Textures/guns/9/gun", 1);
    guns[9].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[9].left_pre.fill_frames("Textures/guns/9/left", 1);
    guns[9].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[9].right_pre.fill_frames("Textures/guns/9/right", 1);
    guns[9].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[9].animation.fill_frames("Textures/guns/9/gun", 1);
    guns[9].left.create(1, 100, 100, 50, 50, 0.1);
    guns[9].left.fill_frames("Textures/guns/9/left", 1);
    guns[9].right.create(1, 100, 100, 50, 50, 0.1);
    guns[9].right.fill_frames("Textures/guns/9/right", 1);
    guns[9].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[9].reload.fill_frames("Textures/guns/9/reload", 1);
    guns[9].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[9].left_reload.fill_frames("Textures/guns/9/left", 1);
    guns[9].right_reload.create(4, 100, 100, 50, 50, 0.1);
    guns[9].right_reload.fill_frames("Textures/guns/9/right_reload", 1);
    guns[9].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[9].crosshair.fill_frames("Textures/guns/9/crosshair", 1);


    for (int i=0; i<3; i++)
    {
        guns[9].animation.frame_pos[i]=0.5;
        guns[9].left.frame_pos[i]=0.5;
        guns[9].right.frame_pos[i]=0.5;
        guns[9].crosshair.frame_pos[i]=0.5;
    }
    for (int i=3; i<6; i++)
    {//setFrame
        guns[9].animation.frame_pos[i]=1.5;
        guns[9].left.frame_pos[i]=0.5;
        guns[9].right.frame_pos[i]=0.5;
        guns[9].crosshair.frame_pos[i]=1.5;
    }



    guns[9].pre.frame_pos[0]=0.1;
    guns[9].left_pre.frame_pos[0]=0.1;
    guns[9].right_pre.frame_pos[0]=0.1;


    guns[9].pre.frame_pos[1]=0.1;
    guns[9].left_pre.frame_pos[1]=0.1;
    guns[9].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<8; i++)
    {
        guns[9].reload.frame_pos[i]=0.1;
        guns[9].left_reload.frame_pos[i]=0.1;
        guns[9].right_reload.frame_pos[i]=3.1;
    }
    for (int i=8; i<16; i++)
    {
        guns[9].reload.frame_pos[i]=0.1;
        guns[9].left_reload.frame_pos[i]=0.1;
        guns[9].right_reload.frame_pos[i]=0.1;
    }
    for (int i=16; i<24; i++)
    {
        guns[9].reload.frame_pos[i]=1.1;
        guns[9].left_reload.frame_pos[i]=0.1;
        guns[9].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<32; i++)
    {
        guns[9].reload.frame_pos[i]=2.1;
        guns[9].left_reload.frame_pos[i]=0.1;
        guns[9].right_reload.frame_pos[i]=2.1;
    }
    for (int i=32; i<40; i++)
    {
        guns[9].reload.frame_pos[i]=1.1;
        guns[9].left_reload.frame_pos[i]=0.1;
        guns[9].right_reload.frame_pos[i]=1.1;
    }
    for (int i=40; i<49; i++)
    {
        guns[9].reload.frame_pos[i]=0.1;
        guns[9].left_reload.frame_pos[i]=0.1;
        guns[9].right_reload.frame_pos[i]=0.1;
    }


    guns[9].buffer.loadFromFile("Sounds/guns/9/0.wav");
    guns[9].sound.setBuffer(guns[9].buffer);

    guns[9].reload_buffer.loadFromFile("Sounds/guns/9/reload0.wav");
    guns[9].reload_sound.setBuffer(guns[9].reload_buffer);

    guns[9].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[9].bullet.setTexture(guns[9].bullet_texture);
    guns[9].bullet.setTextureRect(IntRect(0, 0, 1, 2));


    guns[10].name="The Old Reliable";
    guns[10].cat=1;
    guns[10].x=900;
    guns[10].y=100;
    guns[10].knockback=5;
    guns[10].self_knockback=40;
    guns[10].icon_texture.loadFromFile("Textures/guns/10/icon0.png");
    guns[10].icon.setTexture(guns[10].icon_texture);
    guns[10].damage=48;
    guns[10].spread=0;
    guns[10].create(1, 20, 15, 240);
    guns[10].max_load=1;
    guns[10].max_ammo=1;
    guns[10].isPistol=false;
    guns[10].pre.create(1, 200, 200, 100, 100, 1);
    guns[10].pre.fill_frames("Textures/guns/10/gun", 1);
    guns[10].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[10].left_pre.fill_frames("Textures/guns/10/left", 1);
    guns[10].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[10].right_pre.fill_frames("Textures/guns/10/right", 1);
    guns[10].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[10].animation.fill_frames("Textures/guns/10/gun", 1);
    guns[10].left.create(2, 100, 100, 50, 50, 0.1);
    guns[10].left.fill_frames("Textures/guns/10/left", 1);
    guns[10].right.create(2, 100, 100, 50, 50, 0.1);
    guns[10].right.fill_frames("Textures/guns/10/right", 1);
    guns[10].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[10].reload.fill_frames("Textures/guns/10/reload", 1);
    guns[10].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[10].left_reload.fill_frames("Textures/guns/10/left", 1);
    guns[10].right_reload.create(4, 100, 100, 50, 50, 0.1);
    guns[10].right_reload.fill_frames("Textures/guns/10/right_reload", 1);
    guns[10].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[10].crosshair.fill_frames("Textures/guns/10/crosshair", 1);


    guns[10].animation.frame_pos[0]=0.5;
        guns[10].left.frame_pos[0]=0.5;
        guns[10].right.frame_pos[0]=0.5;
        guns[10].crosshair.frame_pos[0]=0.5;

    for (int i=1; i<21; i++)
    {
        guns[10].animation.frame_pos[i]=1.5;
        guns[10].left.frame_pos[i]=1.5;
        guns[10].right.frame_pos[i]=1.5;
        guns[10].crosshair.frame_pos[i]=1.5;
    }


    guns[10].pre.frame_pos[0]=0.1;
    guns[10].left_pre.frame_pos[0]=0.1;
    guns[10].right_pre.frame_pos[0]=0.1;


    guns[10].pre.frame_pos[1]=0.1;
    guns[10].left_pre.frame_pos[1]=0.1;
    guns[10].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<30; i++)
    {
        guns[10].reload.frame_pos[i]=1.1;
        guns[10].left_reload.frame_pos[i]=0.1;
        guns[10].right_reload.frame_pos[i]=2.1;
    }

    for (int i=30; i<60; i++)
    {
        guns[10].reload.frame_pos[i]=2.1;
        guns[10].left_reload.frame_pos[i]=0.1;
        guns[10].right_reload.frame_pos[i]=3.1;
    }
    for (int i=60; i<90; i++)
    {
        guns[10].reload.frame_pos[i]=0.1;
        guns[10].left_reload.frame_pos[i]=0.1;
        guns[10].right_reload.frame_pos[i]=1.1;
    }
    for (int i=90; i<120; i++)
    {
        guns[10].reload.frame_pos[i]=0.1;
        guns[10].left_reload.frame_pos[i]=0.1;
        guns[10].right_reload.frame_pos[i]=0.1;
    }
    for (int i=120; i<150; i++)
    {
        guns[10].reload.frame_pos[i]=0.1;
        guns[10].left_reload.frame_pos[i]=0.1;
        guns[10].right_reload.frame_pos[i]=1.1;
    }
    for (int i=150; i<180; i++)
    {
        guns[10].reload.frame_pos[i]=0.1;
        guns[10].left_reload.frame_pos[i]=0.1;
        guns[10].right_reload.frame_pos[i]=0.1;
    }
    for (int i=180; i<210; i++)
    {
        guns[10].reload.frame_pos[i]=0.1;
        guns[10].left_reload.frame_pos[i]=0.1;
        guns[10].right_reload.frame_pos[i]=1.1;
    }
    for (int i=210; i<241; i++)
    {
        guns[10].reload.frame_pos[i]=0.1;
        guns[10].left_reload.frame_pos[i]=0.1;
        guns[10].right_reload.frame_pos[i]=0.1;
    }


    guns[10].buffer.loadFromFile("Sounds/guns/10/0.wav");
    guns[10].sound.setBuffer(guns[10].buffer);

    guns[10].reload_buffer.loadFromFile("Sounds/guns/10/reload0.wav");
    guns[10].reload_sound.setBuffer(guns[10].reload_buffer);

    guns[10].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[10].bullet.setTexture(guns[10].bullet_texture);
    guns[10].bullet.setTextureRect(IntRect(0, 0, 1, 2));


    guns[11].name="The Double Barrel";
    guns[11].cat=0;
    guns[11].x=750;
    guns[11].y=100;
    guns[11].knockback=2;
    guns[11].self_knockback=15;
    guns[11].icon_texture.loadFromFile("Textures/guns/11/icon0.png");
    guns[11].icon.setTexture(guns[11].icon_texture);
    guns[11].damage=14;
    guns[11].spread=0;
    guns[11].create(1, 20, 15, 90);
    guns[11].max_load=2;
    guns[11].max_ammo=2;
    guns[11].isPistol=false;
    guns[11].pre.create(1, 200, 200, 100, 100, 1);
    guns[11].pre.fill_frames("Textures/guns/11/gun", 1);
    guns[11].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[11].left_pre.fill_frames("Textures/guns/11/left", 1);
    guns[11].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[11].right_pre.fill_frames("Textures/guns/11/right", 1);
    guns[11].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[11].animation.fill_frames("Textures/guns/11/gun", 1);
    guns[11].left.create(2, 100, 100, 50, 50, 0.1);
    guns[11].left.fill_frames("Textures/guns/11/left", 1);
    guns[11].right.create(2, 100, 100, 50, 50, 0.1);
    guns[11].right.fill_frames("Textures/guns/11/right", 1);
    guns[11].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[11].reload.fill_frames("Textures/guns/11/reload", 1);
    guns[11].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[11].left_reload.fill_frames("Textures/guns/11/left", 1);
    guns[11].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[11].right_reload.fill_frames("Textures/guns/11/right_reload", 1);
    guns[11].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[11].crosshair.fill_frames("Textures/guns/11/crosshair", 1);




    for (int i=0; i<10; i++)
    {
        guns[11].animation.frame_pos[i]=0.5;
        guns[11].left.frame_pos[i]=0.5;
        guns[11].right.frame_pos[i]=0.5;
        guns[11].crosshair.frame_pos[i]=0.5;
    }

    for (int i=10; i<21; i++)
    {
        guns[11].animation.frame_pos[i]=1.5;
        guns[11].left.frame_pos[i]=1.5;
        guns[11].right.frame_pos[i]=1.5;
        guns[11].crosshair.frame_pos[i]=1.5;
    }


    guns[11].pre.frame_pos[0]=0.1;
    guns[11].left_pre.frame_pos[0]=0.1;
    guns[11].right_pre.frame_pos[0]=0.1;


    guns[11].pre.frame_pos[1]=0.1;
    guns[11].left_pre.frame_pos[1]=0.1;
    guns[11].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<15; i++)
    {
        guns[11].reload.frame_pos[i]=2.1;
        guns[11].left_reload.frame_pos[i]=0.1;
        guns[11].right_reload.frame_pos[i]=3.1;
    }
    for (int i=15; i<30; i++)
    {
        guns[11].reload.frame_pos[i]=1.1;
        guns[11].left_reload.frame_pos[i]=0.1;
        guns[11].right_reload.frame_pos[i]=4.1;
    }
    for (int i=30; i<45; i++)
    {
        guns[11].reload.frame_pos[i]=0.1;
        guns[11].left_reload.frame_pos[i]=0.1;
        guns[11].right_reload.frame_pos[i]=3.1;
    }
    for (int i=45; i<60; i++)
    {
        guns[11].reload.frame_pos[i]=0.1;
        guns[11].left_reload.frame_pos[i]=0.1;
        guns[11].right_reload.frame_pos[i]=2.1;
    }
    for (int i=60; i<75; i++)
    {
        guns[11].reload.frame_pos[i]=0.1;
        guns[11].left_reload.frame_pos[i]=0.1;
        guns[11].right_reload.frame_pos[i]=1.1;
    }
    for (int i=75; i<91; i++)
    {
        guns[11].reload.frame_pos[i]=0.1;
        guns[11].left_reload.frame_pos[i]=0.1;
        guns[11].right_reload.frame_pos[i]=0.1;
    }



    guns[11].buffer.loadFromFile("Sounds/guns/11/0.wav");
    guns[11].sound.setBuffer(guns[11].buffer);

    guns[11].reload_buffer.loadFromFile("Sounds/guns/11/reload0.wav");
    guns[11].reload_sound.setBuffer(guns[11].reload_buffer);

    guns[11].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[11].bullet.setTexture(guns[11].bullet_texture);
    guns[11].bullet.setTextureRect(IntRect(0, 0, 1, 2));




    guns[12].name="Auto Shotgun";
    guns[12].cat=0;
    guns[12].x=900;
    guns[12].y=100;
    guns[12].knockback=2;
    guns[12].icon_texture.loadFromFile("Textures/guns/12/icon0.png");
    guns[12].icon.setTexture(guns[12].icon_texture);
    guns[12].damage=6;
    guns[12].spread=1;
    guns[12].create(1, 15, 15, 68);
    guns[12].max_load=18;
    guns[12].max_ammo=18;
    guns[12].isPistol=false;
    guns[12].pre.create(1, 200, 200, 100, 100, 1);
    guns[12].pre.fill_frames("Textures/guns/12/gun", 1);
    guns[12].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[12].left_pre.fill_frames("Textures/guns/12/left", 1);
    guns[12].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[12].right_pre.fill_frames("Textures/guns/12/right", 1);
    guns[12].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[12].animation.fill_frames("Textures/guns/12/gun", 1);
    guns[12].left.create(2, 100, 100, 50, 50, 0.1);
    guns[12].left.fill_frames("Textures/guns/12/left", 1);
    guns[12].right.create(2, 100, 100, 50, 50, 0.1);
    guns[12].right.fill_frames("Textures/guns/12/right", 1);
    guns[12].reload.create(4, 200, 200, 100, 100, 0.1);
    guns[12].reload.fill_frames("Textures/guns/12/reload", 1);
    guns[12].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[12].left_reload.fill_frames("Textures/guns/12/left", 1);
    guns[12].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[12].right_reload.fill_frames("Textures/guns/12/right_reload", 1);
    guns[12].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[12].crosshair.fill_frames("Textures/guns/12/crosshair", 1);


    for (int i=0; i<8; i++)
    {
        guns[12].animation.frame_pos[i]=0.5;
        guns[12].left.frame_pos[i]=0.5;
        guns[12].right.frame_pos[i]=0.5;
        guns[12].crosshair.frame_pos[i]=0.5;
    }
    for (int i=8; i<16; i++)
    {//setFrame
        guns[12].animation.frame_pos[i]=1.5;
        guns[12].left.frame_pos[i]=1.5;
        guns[12].right.frame_pos[i]=1.5;
        guns[12].crosshair.frame_pos[i]=1.5;
    }

    guns[12].pre.frame_pos[0]=0.1;
    guns[12].left_pre.frame_pos[0]=0.1;
    guns[12].right_pre.frame_pos[0]=0.1;


    guns[12].pre.frame_pos[1]=0.1;
    guns[12].left_pre.frame_pos[1]=0.1;
    guns[12].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<8; i++)
    {
        guns[12].reload.frame_pos[i]=0.1;
        guns[12].left_reload.frame_pos[i]=0.1;
        guns[12].right_reload.frame_pos[i]=3.1;
    }
    for (int i=8; i<16; i++)
    {
        guns[12].reload.frame_pos[i]=3.1;
        guns[12].left_reload.frame_pos[i]=0.1;
        guns[12].right_reload.frame_pos[i]=4.1;
    }
    for (int i=16; i<24; i++)
    {
        guns[12].reload.frame_pos[i]=0.1;
        guns[12].left_reload.frame_pos[i]=0.1;
        guns[12].right_reload.frame_pos[i]=3.1;
    }
    for (int i=24; i<34; i++)
    {
        guns[12].reload.frame_pos[i]=0.1;
        guns[12].left_reload.frame_pos[i]=0.1;
        guns[12].right_reload.frame_pos[i]=0.1;
    }
    for (int i=34; i<42; i++)
    {
        guns[12].reload.frame_pos[i]=1.1;
        guns[12].left_reload.frame_pos[i]=0.1;
        guns[12].right_reload.frame_pos[i]=1.1;
    }
    for (int i=42; i<52; i++)
    {
        guns[12].reload.frame_pos[i]=2.1;
        guns[12].left_reload.frame_pos[i]=0.1;
        guns[12].right_reload.frame_pos[i]=2.1;
    }
    for (int i=52; i<60; i++)
    {
        guns[12].reload.frame_pos[i]=1.1;
        guns[12].left_reload.frame_pos[i]=0.1;
        guns[12].right_reload.frame_pos[i]=1.1;
    }
    for (int i=60; i<69; i++)
    {
        guns[12].reload.frame_pos[i]=0.1;
        guns[12].left_reload.frame_pos[i]=0.1;
        guns[12].right_reload.frame_pos[i]=0.1;
    }

    guns[12].buffer.loadFromFile("Sounds/guns/12/0.wav");
    guns[12].sound.setBuffer(guns[12].buffer);

    guns[12].reload_buffer.loadFromFile("Sounds/guns/12/reload0.wav");
    guns[12].reload_sound.setBuffer(guns[12].reload_buffer);

    guns[12].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[12].bullet.setTexture(guns[12].bullet_texture);
    guns[12].bullet.setTextureRect(IntRect(0, 0, 1, 2));




    guns[13].name="Quad Barrel Rocket Launcher";
    guns[13].cat=2;
    guns[13].x=750;
    guns[13].y=100;
    guns[13].radius=150;
    guns[13].splash_multiplier=1;
    guns[13].icon_texture.loadFromFile("Textures/guns/13/icon0.png");
    guns[13].icon.setTexture(guns[13].icon_texture);
    guns[13].damage=80;
    guns[13].proj_speed=50;
    guns[13].spread=0;
    guns[13].create(1, 60, 20, 81);
    guns[13].max_load=1;
    guns[13].max_ammo=4;
    guns[13].isPistol=true;
    guns[13].pre.create(1, 200, 200, 100, 100, 1);
    guns[13].pre.fill_frames("Textures/guns/13/gun", 1);
    guns[13].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[13].left_pre.fill_frames("Textures/guns/13/left", 1);
    guns[13].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[13].right_pre.fill_frames("Textures/guns/13/right", 1);
    guns[13].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[13].animation.fill_frames("Textures/guns/13/gun", 1);
    guns[13].left.create(1, 100, 100, 50, 50, 0.1);
    guns[13].left.fill_frames("Textures/guns/13/left", 1);
    guns[13].right.create(1, 100, 100, 50, 50, 0.1);
    guns[13].right.fill_frames("Textures/guns/13/right", 1);
    guns[13].reload.create(2, 200, 200, 100, 100, 0.1);
    guns[13].reload.fill_frames("Textures/guns/13/reload", 1);
    guns[13].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[13].left_reload.fill_frames("Textures/guns/13/left_reload", 1);
    guns[13].right_reload.create(3, 100, 100, 50, 50, 0.1);
    guns[13].right_reload.fill_frames("Textures/guns/13/right_reload", 1);
    guns[13].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[13].crosshair.fill_frames("Textures/guns/13/crosshair", 1);
    guns[13].isProjectile=true;
    guns[13].projectile.create(2, 100, 20, 50, 10, 0.1);
    guns[13].projectile.fill_frames("Textures/guns/13/projectile", 1);

    guns[13].blast.create(3, 300, 300, 150, 150, 0.15);
    guns[13].blast.fill_frames("Textures/guns/13/blast", 1);

    guns[13].max_projectile_time=21;
    guns[13].blast.frame_pos=new double[22];
    guns[13].blast.f_count=22;

    for (int i=0; i<7; i++)
    {
        guns[13].blast.frame_pos[i]=2.1;
    }

    for (int i=7; i<14; i++)
    {
        guns[13].blast.frame_pos[i]=1.1;
    }

    for (int i=14; i<22; i++)
    {
        guns[13].blast.frame_pos[i]=0.1;
    }

    guns[13].projectile.frame_pos=new double[25];
    guns[13].projectile.f_count=25;

    for (int i=18; i<25; i++)
    {
        guns[13].projectile.frame_pos[i]=0.1;
    }
    for (int i=12; i<18; i++)
    {
        guns[13].projectile.frame_pos[i]=1.1;
    }
    for (int i=6; i<12; i++)
    {
        guns[13].projectile.frame_pos[i]=0.1;
    }
    for (int i=0; i<6; i++)
    {
        guns[13].projectile.frame_pos[i]=1.1;
    }

    //guns[6].


    for (int i=0; i<45; i++)
    {
        guns[13].animation.frame_pos[i]=0.5;
        guns[13].left.frame_pos[i]=0.5;
        guns[13].right.frame_pos[i]=0.5;
        guns[13].crosshair.frame_pos[i]=0.5;
    }
    for (int i=45; i<61; i++)
    {//setFrame
        guns[13].animation.frame_pos[i]=1.5;
        guns[13].left.frame_pos[i]=0.5;
        guns[13].right.frame_pos[i]=0.5;
        guns[13].crosshair.frame_pos[i]=1.5;
    }



    guns[13].pre.frame_pos[0]=0.1;
    guns[13].left_pre.frame_pos[0]=0.1;
    guns[13].right_pre.frame_pos[0]=0.1;


    guns[13].pre.frame_pos[1]=0.1;
    guns[13].left_pre.frame_pos[1]=0.1;
    guns[13].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<27; i++)
    {
        guns[13].reload.frame_pos[i]=0.1;
        guns[13].left_reload.frame_pos[i]=0.1;
        guns[13].right_reload.frame_pos[i]=2.1;
    }
    for (int i=27; i<54; i++)
    {
        guns[13].reload.frame_pos[i]=1.1;
        guns[13].left_reload.frame_pos[i]=0.1;
        guns[13].right_reload.frame_pos[i]=1.1;
    }
    for (int i=54; i<82; i++)
    {
        guns[13].reload.frame_pos[i]=0.1;
        guns[13].left_reload.frame_pos[i]=0.1;
        guns[13].right_reload.frame_pos[i]=0.1;
    }



    guns[13].buffer.loadFromFile("Sounds/guns/13/0.wav");
    guns[13].sound.setBuffer(guns[13].buffer);

    guns[13].reload_buffer.loadFromFile("Sounds/guns/13/reload0.wav");
    guns[13].reload_sound.setBuffer(guns[13].reload_buffer);

    guns[13].exp_buffer.loadFromFile("Sounds/guns/13/explosion0.wav");



    guns[14].name="Rocket Gatling";
    guns[14].cat=2;
    guns[14].x=900;
    guns[14].y=100;
    guns[14].radius=100;
    guns[14].self_explosion_knockback=60;
    guns[14].explosion_knockback=30;
    guns[14].self_damage_multiplier=0.6;
    guns[14].splash_multiplier=1;
    guns[14].icon_texture.loadFromFile("Textures/guns/14/icon0.png");
    guns[14].icon.setTexture(guns[14].icon_texture);
    guns[14].damage=36;
    guns[14].proj_speed=75;
    guns[14].spread=3;
    guns[14].create(1, 12, 25, 132);
    guns[14].max_load=20;
    guns[14].max_ammo=20;
    guns[14].isPistol=false;
    guns[14].pre.create(1, 200, 200, 100, 100, 1);
    guns[14].pre.fill_frames("Textures/guns/14/gun", 1);
    guns[14].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[14].left_pre.fill_frames("Textures/guns/14/left", 1);
    guns[14].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[14].right_pre.fill_frames("Textures/guns/14/right", 1);
    guns[14].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[14].animation.fill_frames("Textures/guns/14/gun", 1);
    guns[14].left.create(1, 100, 100, 50, 50, 0.1);
    guns[14].left.fill_frames("Textures/guns/14/left", 1);
    guns[14].right.create(1, 100, 100, 50, 50, 0.1);
    guns[14].right.fill_frames("Textures/guns/14/right", 1);
    guns[14].reload.create(5, 200, 200, 100, 100, 0.1);
    guns[14].reload.fill_frames("Textures/guns/14/reload", 1);
    guns[14].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[14].left_reload.fill_frames("Textures/guns/14/left", 1);
    guns[14].right_reload.create(6, 100, 100, 50, 50, 0.1);
    guns[14].right_reload.fill_frames("Textures/guns/14/right_reload", 1);
    guns[14].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[14].crosshair.fill_frames("Textures/guns/14/crosshair", 1);
    guns[14].isProjectile=true;
    guns[14].projectile.create(2, 40, 6, 40, 0, 0.1);
    guns[14].projectile.fill_frames("Textures/guns/14/projectile", 1);

    guns[14].blast.create(3, 200, 200, 100, 100, 0.15);
    guns[14].blast.fill_frames("Textures/guns/14/blast", 1);

    guns[14].max_projectile_time=15;
    guns[14].blast.frame_pos=new double[17];
    guns[14].blast.f_count=17;
//setPR
    for (int i=0; i<5; i++)
    {
        guns[14].blast.frame_pos[i]=2.1;
    }

    for (int i=5; i<10; i++)
    {
        guns[14].blast.frame_pos[i]=1.1;
    }

    for (int i=10; i<17; i++)
    {
        guns[14].blast.frame_pos[i]=0.1;
    }

    guns[14].projectile.frame_pos=new double[16];
    guns[14].projectile.f_count=16;

    for (int i=12; i<16; i++)
    {
        guns[14].projectile.frame_pos[i]=0.1;
    }
    for (int i=8; i<12; i++)
    {
        guns[14].projectile.frame_pos[i]=1.1;
    }
    for (int i=4; i<8; i++)
    {
        guns[14].projectile.frame_pos[i]=0.1;
    }
    for (int i=0; i<4; i++)
    {
        guns[14].projectile.frame_pos[i]=1.1;
    }

    //guns[6].


    for (int i=0; i<6; i++)
    {
        guns[14].animation.frame_pos[i]=0.5;
        guns[14].left.frame_pos[i]=0.5;
        guns[14].right.frame_pos[i]=0.5;
        guns[14].crosshair.frame_pos[i]=0.5;
    }
    for (int i=6; i<13; i++)
    {//setFrame
        guns[14].animation.frame_pos[i]=1.5;
        guns[14].left.frame_pos[i]=0.5;
        guns[14].right.frame_pos[i]=0.5;
        guns[14].crosshair.frame_pos[i]=1.5;
    }



    guns[14].pre.frame_pos[0]=0.1;
    guns[14].left_pre.frame_pos[0]=0.1;
    guns[14].right_pre.frame_pos[0]=0.1;


    guns[14].pre.frame_pos[1]=0.1;
    guns[14].left_pre.frame_pos[1]=0.1;
    guns[14].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<12; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=48; i<60; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=60; i<72; i++)
    {
        guns[14].reload.frame_pos[i]=4.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=5.1;
    }
    for (int i=72; i<84; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=84; i<96; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=96; i<108; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=108; i<120; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=120; i<133; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }



    guns[14].buffer.loadFromFile("Sounds/guns/14/0.wav");
    guns[14].sound.setBuffer(guns[14].buffer);

    guns[14].reload_buffer.loadFromFile("Sounds/guns/14/reload0.wav");
    guns[14].reload_sound.setBuffer(guns[14].reload_buffer);

    guns[14].exp_buffer.loadFromFile("Sounds/guns/14/explosion0.wav");


    guns[15].name="Alien Handgun";
    guns[15].cat=1;
    guns[15].x=1050;
    guns[15].y=100;
    guns[15].radius=25;
    guns[15].self_explosion_knockback=0;
    guns[15].explosion_knockback=0;
    guns[15].self_damage_multiplier=0;
    guns[15].splash_multiplier=2;
    guns[15].icon_texture.loadFromFile("Textures/guns/15/icon0.png");
    guns[15].icon.setTexture(guns[15].icon_texture);
    guns[15].damage=66;
    guns[15].proj_speed=150;
    guns[15].spread=0;
    guns[15].create(1, 40, 10, 1);
    guns[15].max_load=0;
    guns[15].max_ammo=0;
    guns[15].ammo_used=0;
    guns[15].isPistol=true;
    guns[15].pre.create(1, 200, 200, 100, 100, 1);
    guns[15].pre.fill_frames("Textures/guns/15/gun", 1);
    guns[15].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[15].left_pre.fill_frames("Textures/guns/15/left", 1);
    guns[15].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[15].right_pre.fill_frames("Textures/guns/15/right", 1);
    guns[15].animation.create(1, 200, 200, 100, 100, 0.1);
    guns[15].animation.fill_frames("Textures/guns/15/gun", 1);
    guns[15].left.create(1, 100, 100, 50, 50, 0.1);
    guns[15].left.fill_frames("Textures/guns/15/left", 1);
    guns[15].right.create(1, 100, 100, 50, 50, 0.1);
    guns[15].right.fill_frames("Textures/guns/15/right", 1);

    /*guns[15].reload.create(5, 200, 200, 100, 100, 0.1);
    guns[15].reload.fill_frames("Textures/guns/14/reload", 1);
    guns[15].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[15].left_reload.fill_frames("Textures/guns/14/left", 1);
    guns[15].right_reload.create(6, 100, 100, 50, 50, 0.1);
    guns[15].right_reload.fill_frames("Textures/guns/14/right_reload", 1);*/

    guns[15].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[15].crosshair.fill_frames("Textures/guns/15/crosshair", 1);
    guns[15].isProjectile=true;
    guns[15].projectile.create(1, 20, 12, 20, 6, 0.1);
    guns[15].projectile.fill_frames("Textures/guns/15/projectile", 1);

    guns[15].blast.create(3, 50, 50, 25, 25, 0.15);
    guns[15].blast.fill_frames("Textures/guns/15/blast", 1);

    guns[15].max_projectile_time=15;
    guns[15].blast.frame_pos=new double[16];
    guns[15].blast.f_count=16;
//setPR
    for (int i=0; i<5; i++)
    {
        guns[15].blast.frame_pos[i]=2.1;
    }

    for (int i=5; i<10; i++)
    {
        guns[15].blast.frame_pos[i]=1.1;
    }

    for (int i=10; i<16; i++)
    {
        guns[15].blast.frame_pos[i]=0.1;
    }

    guns[15].projectile.frame_pos=new double[9];
    guns[15].projectile.f_count=9;

    for (int i=0; i<9; i++)
    {
        guns[15].projectile.frame_pos[i]=0.1;
    }


    //guns[6].


    for (int i=0; i<20; i++)
    {
        guns[15].animation.frame_pos[i]=0.5;
        guns[15].left.frame_pos[i]=0.5;
        guns[15].right.frame_pos[i]=0.5;
        guns[15].crosshair.frame_pos[i]=0.5;
    }
    for (int i=20; i<41; i++)
    {//setFrame
        guns[15].animation.frame_pos[i]=0.5;
        guns[15].left.frame_pos[i]=0.5;
        guns[15].right.frame_pos[i]=0.5;
        guns[15].crosshair.frame_pos[i]=1.5;
    }



    guns[15].pre.frame_pos[0]=0.1;
    guns[15].left_pre.frame_pos[0]=0.1;
    guns[15].right_pre.frame_pos[0]=0.1;


    guns[15].pre.frame_pos[1]=0.1;
    guns[15].left_pre.frame_pos[1]=0.1;
    guns[15].right_pre.frame_pos[1]=0.1;


    /*for (int i=0; i<12; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=48; i<60; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=60; i<72; i++)
    {
        guns[14].reload.frame_pos[i]=4.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=5.1;
    }
    for (int i=72; i<84; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=84; i<96; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=96; i<108; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=108; i<120; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=120; i<133; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }*/



    guns[15].buffer.loadFromFile("Sounds/guns/15/0.wav");
    guns[15].sound.setBuffer(guns[15].buffer);

    //guns[14].reload_buffer.loadFromFile("Sounds/guns/14/reload0.wav");
    //guns[14].reload_sound.setBuffer(guns[14].reload_buffer);

    guns[15].exp_buffer.loadFromFile("Sounds/guns/15/explosion0.wav");


    guns[16].name="Plasma Rifle";
    guns[16].cat=0;
    guns[16].x=1050;
    guns[16].y=100;
    guns[16].radius=25;
    guns[16].self_explosion_knockback=0;
    guns[16].explosion_knockback=0;
    guns[16].self_damage_multiplier=0;
    guns[16].splash_multiplier=2;
    guns[16].icon_texture.loadFromFile("Textures/guns/16/icon0.png");
    guns[16].icon.setTexture(guns[16].icon_texture);
    guns[16].damage=20;
    guns[16].proj_speed=150;
    guns[16].spread=0;
    guns[16].create(1, 8, 15, 84);
    guns[16].max_load=25;
    guns[16].max_ammo=25;
    guns[16].isPistol=false;
    guns[16].pre.create(1, 200, 200, 100, 100, 1);
    guns[16].pre.fill_frames("Textures/guns/16/gun", 1);
    guns[16].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[16].left_pre.fill_frames("Textures/guns/16/left", 1);
    guns[16].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[16].right_pre.fill_frames("Textures/guns/16/right", 1);
    guns[16].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[16].animation.fill_frames("Textures/guns/16/gun", 1);
    guns[16].left.create(2, 100, 100, 50, 50, 0.1);
    guns[16].left.fill_frames("Textures/guns/16/left", 1);
    guns[16].right.create(2, 100, 100, 50, 50, 0.1);
    guns[16].right.fill_frames("Textures/guns/16/right", 1);

    guns[16].reload.create(4, 200, 200, 100, 100, 0.1);
    guns[16].reload.fill_frames("Textures/guns/16/reload", 1);
    guns[16].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[16].left_reload.fill_frames("Textures/guns/16/left", 1);
    guns[16].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[16].right_reload.fill_frames("Textures/guns/16/right_reload", 1);

    guns[16].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[16].crosshair.fill_frames("Textures/guns/16/crosshair", 1);
    guns[16].isProjectile=true;
    guns[16].projectile.create(1, 20, 12, 20, 6, 0.1);
    guns[16].projectile.fill_frames("Textures/guns/16/projectile", 1);

    guns[16].blast.create(3, 50, 50, 25, 25, 0.15);
    guns[16].blast.fill_frames("Textures/guns/16/blast", 1);

    guns[16].max_projectile_time=15;
    guns[16].blast.frame_pos=new double[16];
    guns[16].blast.f_count=16;
//setPR
    for (int i=0; i<5; i++)
    {
        guns[16].blast.frame_pos[i]=2.1;
    }

    for (int i=5; i<10; i++)
    {
        guns[16].blast.frame_pos[i]=1.1;
    }

    for (int i=10; i<16; i++)
    {
        guns[16].blast.frame_pos[i]=0.1;
    }

    guns[16].projectile.frame_pos=new double[9];
    guns[16].projectile.f_count=9;

    for (int i=0; i<9; i++)
    {
        guns[16].projectile.frame_pos[i]=0.1;
    }


    //guns[6].


    for (int i=0; i<4; i++)
    {
        guns[16].animation.frame_pos[i]=0.5;
        guns[16].left.frame_pos[i]=0.5;
        guns[16].right.frame_pos[i]=0.5;
        guns[16].crosshair.frame_pos[i]=0.5;
    }
    for (int i=4; i<9; i++)
    {//setFrame
        guns[16].animation.frame_pos[i]=1.5;
        guns[16].left.frame_pos[i]=1.5;
        guns[16].right.frame_pos[i]=1.5;
        guns[16].crosshair.frame_pos[i]=1.5;
    }



    guns[16].pre.frame_pos[0]=0.1;
    guns[16].left_pre.frame_pos[0]=0.1;
    guns[16].right_pre.frame_pos[0]=0.1;


    guns[16].pre.frame_pos[1]=0.1;
    guns[16].left_pre.frame_pos[1]=0.1;
    guns[16].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<12; i++)
    {
        guns[16].reload.frame_pos[i]=3.1;
        guns[16].left_reload.frame_pos[i]=0.1;
        guns[16].right_reload.frame_pos[i]=4.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[16].reload.frame_pos[i]=0.1;
        guns[16].left_reload.frame_pos[i]=0.1;
        guns[16].right_reload.frame_pos[i]=3.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[16].reload.frame_pos[i]=0.1;
        guns[16].left_reload.frame_pos[i]=0.1;
        guns[16].right_reload.frame_pos[i]=0.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[16].reload.frame_pos[i]=1.1;
        guns[16].left_reload.frame_pos[i]=0.1;
        guns[16].right_reload.frame_pos[i]=1.1;
    }
    for (int i=48; i<60; i++)
    {
        guns[16].reload.frame_pos[i]=2.1;
        guns[16].left_reload.frame_pos[i]=0.1;
        guns[16].right_reload.frame_pos[i]=2.1;
    }
    for (int i=60; i<72; i++)
    {
        guns[16].reload.frame_pos[i]=1.1;
        guns[16].left_reload.frame_pos[i]=0.1;
        guns[16].right_reload.frame_pos[i]=1.1;
    }
    for (int i=72; i<85; i++)
    {
        guns[16].reload.frame_pos[i]=0.1;
        guns[16].left_reload.frame_pos[i]=0.1;
        guns[16].right_reload.frame_pos[i]=0.1;
    }

    /*for (int i=0; i<12; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=48; i<60; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=60; i<72; i++)
    {
        guns[14].reload.frame_pos[i]=4.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=5.1;
    }
    for (int i=72; i<84; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=84; i<96; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=96; i<108; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=108; i<120; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=120; i<133; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }*/



    guns[16].buffer.loadFromFile("Sounds/guns/16/0.wav");
    guns[16].sound.setBuffer(guns[16].buffer);

    guns[16].reload_buffer.loadFromFile("Sounds/guns/16/reload0.wav");
    guns[16].reload_sound.setBuffer(guns[16].reload_buffer);

    guns[16].exp_buffer.loadFromFile("Sounds/guns/16/explosion0.wav");




    guns[17].name="Flamethrower";
    guns[17].cat=2;
    guns[17].x=1050;
    guns[17].y=100;
    guns[17].radius=25;
    guns[17].ammo_used=0;
    guns[17].proj_acceleration=-2;
    guns[17].max_distance=600;
    guns[17].self_explosion_knockback=0;
    guns[17].explosion_knockback=0;
    guns[17].self_damage_multiplier=0;
    guns[17].splash_multiplier=1;
    guns[17].icon_texture.loadFromFile("Textures/guns/17/icon0.png");
    guns[17].icon.setTexture(guns[17].icon_texture);
    guns[17].damage=6;
    guns[17].proj_speed=50;
    guns[17].knockback=2;
    guns[17].spread=6;
    guns[17].create(1, 2, 20, 1);
    guns[17].max_load=0;
    guns[17].max_ammo=0;
    guns[17].isPistol=false;
    guns[17].pre.create(1, 200, 200, 100, 100, 1);
    guns[17].pre.fill_frames("Textures/guns/17/gun", 1);
    guns[17].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[17].left_pre.fill_frames("Textures/guns/17/left", 1);
    guns[17].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[17].right_pre.fill_frames("Textures/guns/17/right", 1);
    guns[17].animation.create(1, 200, 200, 100, 100, 0.1);
    guns[17].animation.fill_frames("Textures/guns/17/gun", 1);
    guns[17].left.create(1, 100, 100, 50, 50, 0.1);
    guns[17].left.fill_frames("Textures/guns/17/left", 1);
    guns[17].right.create(1, 100, 100, 50, 50, 0.1);
    guns[17].right.fill_frames("Textures/guns/17/right", 1);

    /*guns[16].reload.create(4, 200, 200, 100, 100, 0.1);
    guns[16].reload.fill_frames("Textures/guns/16/reload", 1);
    guns[16].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[16].left_reload.fill_frames("Textures/guns/16/left", 1);
    guns[16].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[16].right_reload.fill_frames("Textures/guns/16/right_reload", 1);*/

    guns[17].crosshair.create(1, 200, 200, 100, 100, 0.1);
    guns[17].crosshair.fill_frames("Textures/guns/17/crosshair", 1);
    guns[17].isProjectile=true;
    guns[17].projectile.create(3, 100, 40, 0, 20, 0.1);
    guns[17].projectile.fill_frames("Textures/guns/17/projectile", 1);

    guns[17].blast.create(3, 50, 100, 25, 50, 0.15);
    guns[17].blast.fill_frames("Textures/guns/17/blast", 1);

    guns[17].max_projectile_time=15;
    guns[17].blast.frame_pos=new double[16];
    guns[17].blast.f_count=16;
//setPR
    for (int i=0; i<5; i++)
    {
        guns[17].blast.frame_pos[i]=2.1;
    }

    for (int i=5; i<10; i++)
    {
        guns[17].blast.frame_pos[i]=1.1;
    }

    for (int i=10; i<16; i++)
    {
        guns[17].blast.frame_pos[i]=0.1;
    }

    guns[17].projectile.frame_pos=new double[20];
    guns[17].projectile.f_count=20;

    for (int i=0; i<4; i++)
    {
        guns[17].projectile.frame_pos[i]=2.1;
    }
    for (int i=4; i<7; i++)
    {
        guns[17].projectile.frame_pos[i]=1.1;
    }
    for (int i=7; i<21; i++)
    {
        guns[17].projectile.frame_pos[i]=0.1;
    }


    //guns[6].


    for (int i=0; i<3; i++)
    {
        guns[17].animation.frame_pos[i]=0.5;
        guns[17].left.frame_pos[i]=0.5;
        guns[17].right.frame_pos[i]=0.5;
        guns[17].crosshair.frame_pos[i]=0.5;
    }



    guns[17].pre.frame_pos[0]=0.1;
    guns[17].left_pre.frame_pos[0]=0.1;
    guns[17].right_pre.frame_pos[0]=0.1;


    guns[17].pre.frame_pos[1]=0.1;
    guns[17].left_pre.frame_pos[1]=0.1;
    guns[17].right_pre.frame_pos[1]=0.1;




    /*for (int i=0; i<12; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=48; i<60; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=60; i<72; i++)
    {
        guns[14].reload.frame_pos[i]=4.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=5.1;
    }
    for (int i=72; i<84; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=84; i<96; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=96; i<108; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=108; i<120; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=120; i<133; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }*/



    guns[17].buffer.loadFromFile("Sounds/guns/17/0.wav");
    guns[17].sound.setBuffer(guns[17].buffer);



    guns[17].exp_buffer.loadFromFile("Sounds/guns/17/0.wav");



    guns[18].name="Gauss Gun";
    guns[18].cat=2;
    guns[18].x=300;
    guns[18].y=250;
    guns[18].knockback=6;
    guns[18].icon_texture.loadFromFile("Textures/guns/18/icon0.png");
    guns[18].icon.setTexture(guns[18].icon_texture);
    guns[18].damage=75;
    guns[18].spread=0;
    guns[18].create(1, 60, 15, 80);
    guns[18].max_load=6;
    guns[18].max_ammo=6;
    guns[18].isPistol=false;
    guns[18].pre.create(1, 200, 200, 100, 100, 1);
    guns[18].pre.fill_frames("Textures/guns/18/gun", 1);
    guns[18].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[18].left_pre.fill_frames("Textures/guns/18/left", 1);
    guns[18].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[18].right_pre.fill_frames("Textures/guns/18/right", 1);
    guns[18].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[18].animation.fill_frames("Textures/guns/18/gun", 1);
    guns[18].left.create(2, 100, 100, 50, 50, 0.1);
    guns[18].left.fill_frames("Textures/guns/18/left", 1);
    guns[18].right.create(2, 100, 100, 50, 50, 0.1);
    guns[18].right.fill_frames("Textures/guns/18/right", 1);
    guns[18].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[18].reload.fill_frames("Textures/guns/18/reload", 1);
    guns[18].left_reload.create(3, 100, 100, 50, 50, 0.1);
    guns[18].left_reload.fill_frames("Textures/guns/18/left_reload", 1);
    guns[18].right_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[18].right_reload.fill_frames("Textures/guns/18/right", 1);
    guns[18].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[18].crosshair.fill_frames("Textures/guns/18/crosshair", 1);
    //std::cout << "Test1";


    for (int i=0; i<24; i++)
    {
        guns[18].animation.frame_pos[i]=0.5;
        guns[18].left.frame_pos[i]=0.5;
        guns[18].right.frame_pos[i]=0.5;
        guns[18].crosshair.frame_pos[i]=0.5;
    }
    for (int i=24; i<61; i++)
    {
        guns[18].animation.frame_pos[i]=1.5;
        guns[18].left.frame_pos[i]=1.5;
        guns[18].right.frame_pos[i]=1.5;
        guns[18].crosshair.frame_pos[i]=1.5;


    }
    //std::cout << "Test2";


    for (int i=0; i<16; i++)
    {
        guns[18].reload.frame_pos[i]=0.5;
        guns[18].left_reload.frame_pos[i]=0.5;
        guns[18].right_reload.frame_pos[i]=0.5;
        //guns[5].crosshair.frame_pos[i]=0.5;
    }
    for (int i=16; i<32; i++)
    {
        guns[18].reload.frame_pos[i]=1.5;
        guns[18].left_reload.frame_pos[i]=1.5;
        guns[18].right_reload.frame_pos[i]=0.5;
        //guns[5].crosshair.frame_pos[i]=0.5;
    }
    for (int i=32; i<48; i++)
    {
        guns[18].reload.frame_pos[i]=2.5;
        guns[18].left_reload.frame_pos[i]=2.5;
        guns[18].right_reload.frame_pos[i]=0.5;
        //guns[1].crosshair.frame_pos[i]=0.5;
    }
    for (int i=48; i<64; i++)
    {
        guns[18].reload.frame_pos[i]=1.5;
        guns[18].left_reload.frame_pos[i]=1.5;
        guns[18].right_reload.frame_pos[i]=0.5;
        //guns[1].crosshair.frame_pos[i]=0.5;
    }
    for (int i=64; i<81; i++)
    {
        guns[18].reload.frame_pos[i]=0.5;
        guns[18].left_reload.frame_pos[i]=0.5;
        guns[18].right_reload.frame_pos[i]=0.5;
        //guns[1].crosshair.frame_pos[i]=0.5;
    }







    guns[18].pre.frame_pos[0]=0.1;
    guns[18].left_pre.frame_pos[0]=0.1;
    guns[18].right_pre.frame_pos[0]=0.1;


    guns[18].pre.frame_pos[1]=0.1;
    guns[18].left_pre.frame_pos[1]=0.1;
    guns[18].right_pre.frame_pos[1]=0.1;





    guns[18].buffer.loadFromFile("Sounds/guns/18/0.wav");
    guns[18].sound.setBuffer(guns[18].buffer);

    guns[18].reload_buffer.loadFromFile("Sounds/guns/18/reload0.wav");
    guns[18].reload_sound.setBuffer(guns[18].reload_buffer);

    guns[18].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[18].bullet.setTexture(guns[18].bullet_texture);
    guns[18].bullet.setTextureRect(IntRect(0, 0, 1, 2));





    guns[19].name="Laser Pistol";
    guns[19].cat=1;
    guns[19].x=300;
    guns[19].y=250;
    guns[19].knockback=0;
    guns[19].icon_texture.loadFromFile("Textures/guns/19/icon0.png");
    guns[19].icon.setTexture(guns[19].icon_texture);
    guns[19].damage=144;
    guns[19].spread=0;
    guns[19].create(1, 165, 15, 180);
    guns[19].max_load=3;
    guns[19].max_ammo=3;
    guns[19].isPistol=true;
    guns[19].pre.create(1, 200, 200, 100, 100, 1);
    guns[19].pre.fill_frames("Textures/guns/19/gun", 1);
    guns[19].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[19].left_pre.fill_frames("Textures/guns/19/left", 1);
    guns[19].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[19].right_pre.fill_frames("Textures/guns/19/right", 1);
    guns[19].animation.create(1, 200, 200, 100, 100, 0.1);
    guns[19].animation.fill_frames("Textures/guns/19/gun", 1);
    guns[19].left.create(1, 100, 100, 50, 50, 0.1);
    guns[19].left.fill_frames("Textures/guns/19/left", 1);
    guns[19].right.create(1, 100, 100, 50, 50, 0.1);
    guns[19].right.fill_frames("Textures/guns/19/right", 1);
    guns[19].reload.create(2, 200, 200, 100, 100, 0.1);
    guns[19].reload.fill_frames("Textures/guns/19/reload", 1);
    guns[19].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[19].left_reload.fill_frames("Textures/guns/19/left", 1);
    guns[19].right_reload.create(4, 100, 100, 50, 50, 0.1);
    guns[19].right_reload.fill_frames("Textures/guns/19/right_reload", 1);
    guns[19].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[19].crosshair.fill_frames("Textures/guns/19/crosshair", 1);



    for (int i=0; i<100; i++)
    {//setFrame
        guns[19].animation.frame_pos[i]=0.5;
        guns[19].left.frame_pos[i]=0.5;
        guns[19].right.frame_pos[i]=0.5;
        guns[19].crosshair.frame_pos[i]=0.5;
    }
    for (int i=100; i<166; i++)
    {
        guns[19].animation.frame_pos[i]=0.5;
        guns[19].left.frame_pos[i]=0.5;
        guns[19].right.frame_pos[i]=0.5;
        guns[19].crosshair.frame_pos[i]=1.5;
    }

    guns[19].pre.frame_pos[0]=0.1;
    guns[19].left_pre.frame_pos[0]=0.1;
    guns[19].right_pre.frame_pos[0]=0.1;


    guns[19].pre.frame_pos[1]=0.1;
    guns[19].left_pre.frame_pos[1]=0.1;
    guns[19].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<30; i++)
    {
        guns[19].reload.frame_pos[i]=0.1;
        guns[19].left_reload.frame_pos[i]=0.1;
        guns[19].right_reload.frame_pos[i]=3.1;
    }
    for (int i=30; i<60; i++)
    {
        guns[19].reload.frame_pos[i]=0.1;
        guns[19].left_reload.frame_pos[i]=0.1;
        guns[19].right_reload.frame_pos[i]=0.1;
    }
    for (int i=60; i<90; i++)
    {
        guns[19].reload.frame_pos[i]=1.1;
        guns[19].left_reload.frame_pos[i]=0.1;
        guns[19].right_reload.frame_pos[i]=1.1;
    }
    for (int i=90; i<120; i++)
    {
        guns[19].reload.frame_pos[i]=0.1;
        guns[19].left_reload.frame_pos[i]=0.1;
        guns[19].right_reload.frame_pos[i]=2.1;
    }
    for (int i=120; i<150; i++)
    {
        guns[19].reload.frame_pos[i]=1.1;
        guns[19].left_reload.frame_pos[i]=0.1;
        guns[19].right_reload.frame_pos[i]=1.1;
    }
    for (int i=150; i<181; i++)
    {
        guns[19].reload.frame_pos[i]=0.1;
        guns[19].left_reload.frame_pos[i]=0.1;
        guns[19].right_reload.frame_pos[i]=0.1;
    }



    guns[19].buffer.loadFromFile("Sounds/guns/19/0.wav");
    guns[19].sound.setBuffer(guns[19].buffer);

    guns[19].reload_buffer.loadFromFile("Sounds/guns/19/reload0.wav");
    guns[19].reload_sound.setBuffer(guns[19].reload_buffer);

    guns[19].bullet_texture.loadFromFile("Textures/blue_laser.png");
    guns[19].bullet.setTexture(guns[19].bullet_texture);
    guns[19].bullet.setTextureRect(IntRect(0, 0, 1, 2));

    guns[20].name="Golden Machine Gun";
    guns[20].cat=0;
    guns[20].x=300;
    guns[20].y=250;
    guns[20].knockback=6;
    guns[20].icon_texture.loadFromFile("Textures/guns/20/icon0.png");
    guns[20].icon.setTexture(guns[20].icon_texture);
    guns[20].damage=30;
    guns[20].spread=0;
    guns[20].create(1, 15, 15, 68);
    guns[20].max_load=16;
    guns[20].max_ammo=16;
    guns[20].isPistol=false;
    guns[20].pre.create(1, 200, 200, 100, 100, 1);
    guns[20].pre.fill_frames("Textures/guns/20/gun", 1);
    guns[20].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[20].left_pre.fill_frames("Textures/guns/20/left", 1);
    guns[20].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[20].right_pre.fill_frames("Textures/guns/20/right", 1);
    guns[20].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[20].animation.fill_frames("Textures/guns/20/gun", 1);
    guns[20].left.create(2, 100, 100, 50, 50, 0.1);
    guns[20].left.fill_frames("Textures/guns/20/left", 1);
    guns[20].right.create(2, 100, 100, 50, 50, 0.1);
    guns[20].right.fill_frames("Textures/guns/20/right", 1);
    guns[20].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[20].reload.fill_frames("Textures/guns/20/reload", 1);
    guns[20].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[20].left_reload.fill_frames("Textures/guns/20/left", 1);
    guns[20].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[20].right_reload.fill_frames("Textures/guns/20/right_reload", 1);
    guns[20].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[20].crosshair.fill_frames("Textures/guns/20/crosshair", 1);


    for (int i=0; i<8; i++)
    {
        guns[20].animation.frame_pos[i]=0.5;
        guns[20].left.frame_pos[i]=0.5;
        guns[20].right.frame_pos[i]=0.5;
        guns[20].crosshair.frame_pos[i]=0.5;
    }
    for (int i=8; i<16; i++)
    {//setFrame
        guns[20].animation.frame_pos[i]=1.5;
        guns[20].left.frame_pos[i]=1.5;
        guns[20].right.frame_pos[i]=1.5;
        guns[20].crosshair.frame_pos[i]=1.5;
    }

    guns[20].pre.frame_pos[0]=0.1;
    guns[20].left_pre.frame_pos[0]=0.1;
    guns[20].right_pre.frame_pos[0]=0.1;


    guns[20].pre.frame_pos[1]=0.1;
    guns[20].left_pre.frame_pos[1]=0.1;
    guns[20].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<8; i++)
    {
        guns[20].reload.frame_pos[i]=0.1;
        guns[20].left_reload.frame_pos[i]=0.1;
        guns[20].right_reload.frame_pos[i]=3.1;
    }
    for (int i=8; i<16; i++)
    {
        guns[20].reload.frame_pos[i]=0.1;
        guns[20].left_reload.frame_pos[i]=0.1;
        guns[20].right_reload.frame_pos[i]=4.1;
    }
    for (int i=16; i<24; i++)
    {
        guns[20].reload.frame_pos[i]=0.1;
        guns[20].left_reload.frame_pos[i]=0.1;
        guns[20].right_reload.frame_pos[i]=3.1;
    }
    for (int i=24; i<34; i++)
    {
        guns[20].reload.frame_pos[i]=0.1;
        guns[20].left_reload.frame_pos[i]=0.1;
        guns[20].right_reload.frame_pos[i]=0.1;
    }
    for (int i=34; i<42; i++)
    {
        guns[20].reload.frame_pos[i]=1.1;
        guns[20].left_reload.frame_pos[i]=0.1;
        guns[20].right_reload.frame_pos[i]=1.1;
    }
    for (int i=42; i<52; i++)
    {
        guns[20].reload.frame_pos[i]=2.1;
        guns[20].left_reload.frame_pos[i]=0.1;
        guns[20].right_reload.frame_pos[i]=2.1;
    }
    for (int i=52; i<60; i++)
    {
        guns[20].reload.frame_pos[i]=1.1;
        guns[20].left_reload.frame_pos[i]=0.1;
        guns[20].right_reload.frame_pos[i]=1.1;
    }
    for (int i=60; i<69; i++)
    {
        guns[20].reload.frame_pos[i]=0.1;
        guns[20].left_reload.frame_pos[i]=0.1;
        guns[20].right_reload.frame_pos[i]=0.1;
    }

    guns[20].buffer.loadFromFile("Sounds/guns/20/0.wav");
    guns[20].sound.setBuffer(guns[20].buffer);

    guns[20].reload_buffer.loadFromFile("Sounds/guns/20/reload0.wav");
    guns[20].reload_sound.setBuffer(guns[20].reload_buffer);

    guns[20].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[20].bullet.setTexture(guns[20].bullet_texture);
    guns[20].bullet.setTextureRect(IntRect(0, 0, 1, 2));


    guns[21].name="Shotgun";
    guns[21].cat=0;
    guns[21].pellet_spread=0.02;
    guns[21].x=450;
    guns[21].y=250;
    guns[21].knockback=1;
    guns[21].icon_texture.loadFromFile("Textures/guns/21/icon0.png");
    guns[21].icon.setTexture(guns[21].icon_texture);
    guns[21].damage=12;
    guns[21].spread=0;
    guns[21].create(1, 45, 15, 20);
    guns[21].max_load=1;
    guns[21].max_ammo=8;
    guns[21].isPistol=false;
    guns[21].pre.create(1, 200, 200, 100, 100, 1);
    guns[21].pre.fill_frames("Textures/guns/21/gun", 1);
    guns[21].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[21].left_pre.fill_frames("Textures/guns/21/left", 1);
    guns[21].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[21].right_pre.fill_frames("Textures/guns/21/right", 1);
    guns[21].animation.create(3, 200, 200, 100, 100, 0.1);
    guns[21].animation.fill_frames("Textures/guns/21/gun", 1);
    guns[21].left.create(2, 100, 100, 50, 50, 0.1);
    guns[21].left.fill_frames("Textures/guns/21/left", 1);
    guns[21].right.create(3, 100, 100, 50, 50, 0.1);
    guns[21].right.fill_frames("Textures/guns/21/right", 1);
    guns[21].reload.create(2, 200, 200, 100, 100, 0.1);
    guns[21].reload.fill_frames("Textures/guns/21/reload", 1);
    guns[21].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[21].left_reload.fill_frames("Textures/guns/21/left", 1);
    guns[21].right_reload.create(2, 100, 100, 50, 50, 0.1);
    guns[21].right_reload.fill_frames("Textures/guns/21/right_reload", 1);
    guns[21].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[21].crosshair.fill_frames("Textures/guns/21/crosshair", 1);




    for (int i=0; i<6; i++)
    {//setFrame
        guns[21].animation.frame_pos[i]=0.5;
        guns[21].left.frame_pos[i]=0.5;
        guns[21].right.frame_pos[i]=0.5;
        guns[21].crosshair.frame_pos[i]=0.5;
    }
    for (int i=6; i<19; i++)
    {//setFrame
        guns[21].animation.frame_pos[i]=1.5;
        guns[21].left.frame_pos[i]=1.5;
        guns[21].right.frame_pos[i]=1.5;
        guns[21].crosshair.frame_pos[i]=0.5;
    }
    for (int i=19; i<32; i++)
    {//setFrame
        guns[21].animation.frame_pos[i]=2.5;
        guns[21].left.frame_pos[i]=1.5;
        guns[21].right.frame_pos[i]=2.5;
        guns[21].crosshair.frame_pos[i]=1.5;
    }
    for (int i=32; i<46; i++)
    {//setFrame
        guns[21].animation.frame_pos[i]=1.5;
        guns[21].left.frame_pos[i]=1.5;
        guns[21].right.frame_pos[i]=1.5;
        guns[21].crosshair.frame_pos[i]=1.5;
    }

    guns[21].pre.frame_pos[0]=0.1;
    guns[21].left_pre.frame_pos[0]=0.1;
    guns[21].right_pre.frame_pos[0]=0.1;


    guns[21].pre.frame_pos[1]=0.1;
    guns[21].left_pre.frame_pos[1]=0.1;
    guns[21].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<10; i++)
    {
        guns[21].reload.frame_pos[i]=1.1;
        guns[21].left_reload.frame_pos[i]=0.1;
        guns[21].right_reload.frame_pos[i]=1.1;
    }
    for (int i=10; i<21; i++)
    {
        guns[21].reload.frame_pos[i]=0.1;
        guns[21].left_reload.frame_pos[i]=0.1;
        guns[21].right_reload.frame_pos[i]=0.1;
    }


    guns[21].buffer.loadFromFile("Sounds/guns/21/0.wav");
    guns[21].sound.setBuffer(guns[21].buffer);

    guns[21].reload_buffer.loadFromFile("Sounds/guns/21/reload0.wav");
    guns[21].reload_sound.setBuffer(guns[21].reload_buffer);

    guns[21].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[21].bullet.setTexture(guns[21].bullet_texture);
    guns[21].bullet.setTextureRect(IntRect(0, 0, 1, 2));


    guns[22].name="Optic Pistol";
    guns[22].cat=1;
    guns[22].x=450;
    guns[22].y=250;
    guns[22].knockback=0;
    guns[22].icon_texture.loadFromFile("Textures/guns/22/icon0.png");
    guns[22].icon.setTexture(guns[22].icon_texture);
    guns[22].damage=4;
    guns[22].spread=0;
    guns[22].create(1, 2, 10, 40);
    guns[22].max_load=70;
    guns[22].max_ammo=70;
    guns[22].isPistol=true;
    guns[22].pre.create(1, 200, 200, 100, 100, 1);
    guns[22].pre.fill_frames("Textures/guns/22/gun", 1);
    guns[22].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[22].left_pre.fill_frames("Textures/guns/22/left", 1);
    guns[22].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[22].right_pre.fill_frames("Textures/guns/22/right", 1);
    guns[22].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[22].animation.fill_frames("Textures/guns/22/gun", 1);
    guns[22].left.create(1, 100, 100, 50, 50, 0.1);
    guns[22].left.fill_frames("Textures/guns/22/left", 1);
    guns[22].right.create(1, 100, 100, 50, 50, 0.1);
    guns[22].right.fill_frames("Textures/guns/22/right", 1);
    guns[22].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[22].reload.fill_frames("Textures/guns/22/reload", 1);
    guns[22].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[22].left_reload.fill_frames("Textures/guns/22/left", 1);
    guns[22].right_reload.create(3, 100, 100, 50, 50, 0.1);
    guns[22].right_reload.fill_frames("Textures/guns/22/right_reload", 1);
    guns[22].crosshair.create(1, 200, 200, 100, 100, 0.1);
    guns[22].crosshair.fill_frames("Textures/guns/22/crosshair", 1);


    for (int i=1; i<3; i++)
    {
        guns[22].animation.frame_pos[i]=1.5;
        guns[22].left.frame_pos[i]=0.5;
        guns[22].right.frame_pos[i]=0.5;
        guns[22].crosshair.frame_pos[i]=0.5;
    }

        guns[22].animation.frame_pos[0]=0.5;
        guns[22].left.frame_pos[0]=0.5;
        guns[22].right.frame_pos[0]=0.5;
        guns[22].crosshair.frame_pos[0]=0.5;


    guns[22].pre.frame_pos[0]=0.1;
    guns[22].left_pre.frame_pos[0]=0.1;
    guns[22].right_pre.frame_pos[0]=0.1;


    guns[22].pre.frame_pos[1]=0.1;
    guns[22].left_pre.frame_pos[1]=0.1;
    guns[22].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<8; i++)
    {
        guns[22].reload.frame_pos[i]=0.1;
        guns[22].left_reload.frame_pos[i]=0.1;
        guns[22].right_reload.frame_pos[i]=0.1;
    }
    for (int i=8; i<16; i++)
    {
        guns[22].reload.frame_pos[i]=1.1;
        guns[22].left_reload.frame_pos[i]=0.1;
        guns[22].right_reload.frame_pos[i]=1.1;
    }
    for (int i=16; i<24; i++)
    {
        guns[22].reload.frame_pos[i]=2.1;
        guns[22].left_reload.frame_pos[i]=0.1;
        guns[22].right_reload.frame_pos[i]=2.1;
    }
    for (int i=24; i<32; i++)
    {
        guns[22].reload.frame_pos[i]=1.1;
        guns[22].left_reload.frame_pos[i]=0.1;
        guns[22].right_reload.frame_pos[i]=1.1;
    }
    for (int i=32; i<41; i++)
    {
        guns[22].reload.frame_pos[i]=0.1;
        guns[22].left_reload.frame_pos[i]=0.1;
        guns[22].right_reload.frame_pos[i]=0.1;
    }


    guns[22].buffer.loadFromFile("Sounds/guns/22/0.wav");
    guns[22].sound.setBuffer(guns[22].buffer);

    guns[22].reload_buffer.loadFromFile("Sounds/guns/22/reload0.wav");
    guns[22].reload_sound.setBuffer(guns[22].reload_buffer);

    guns[22].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[22].bullet.setTexture(guns[22].bullet_texture);
    guns[22].bullet.setTextureRect(IntRect(0, 0, 1, 2));


    guns[23].name="Electric Arc";
    guns[23].cat=2;
    guns[23].x=450;
    guns[23].y=250;
    guns[23].knockback=0;
    guns[23].icon_texture.loadFromFile("Textures/guns/23/icon0.png");
    guns[23].icon.setTexture(guns[23].icon_texture);
    guns[23].damage=6;
    guns[23].spread=0;
    guns[23].create(1, 3, 15, 40);
    guns[23].max_load=50;
    guns[23].max_ammo=50;
    guns[23].isPistol=false;
    guns[23].pre.create(1, 200, 200, 100, 100, 1);
    guns[23].pre.fill_frames("Textures/guns/23/gun", 1);
    guns[23].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[23].left_pre.fill_frames("Textures/guns/23/left", 1);
    guns[23].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[23].right_pre.fill_frames("Textures/guns/23/right", 1);
    guns[23].animation.create(1, 200, 200, 100, 100, 0.1);
    guns[23].animation.fill_frames("Textures/guns/23/gun", 1);
    guns[23].left.create(1, 100, 100, 50, 50, 0.1);
    guns[23].left.fill_frames("Textures/guns/23/left", 1);
    guns[23].right.create(1, 100, 100, 50, 50, 0.1);
    guns[23].right.fill_frames("Textures/guns/23/right", 1);
    guns[23].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[23].reload.fill_frames("Textures/guns/23/reload", 1);
    guns[23].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[23].left_reload.fill_frames("Textures/guns/23/left_reload", 1);
    guns[23].right_reload.create(3, 100, 100, 50, 50, 0.1);
    guns[23].right_reload.fill_frames("Textures/guns/23/right_reload", 1);
    guns[23].crosshair.create(1, 200, 200, 100, 100, 0.1);
    guns[23].crosshair.fill_frames("Textures/guns/23/crosshair", 1);


    for (int i=0; i<4; i++)
    {

        guns[23].left.frame_pos[i]=0.5;
        guns[23].right.frame_pos[i]=0.5;
        guns[23].crosshair.frame_pos[i]=0.5;
    }
    guns[23].animation.frame_pos[0]=0.5;
    guns[23].animation.frame_pos[1]=3.5;
    guns[23].animation.frame_pos[2]=2.5;
    guns[23].animation.frame_pos[3]=1.5;




    guns[23].pre.frame_pos[0]=0.1;
    guns[23].left_pre.frame_pos[0]=0.1;
    guns[23].right_pre.frame_pos[0]=0.1;


    guns[23].pre.frame_pos[1]=0.1;
    guns[23].left_pre.frame_pos[1]=0.1;
    guns[23].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<8; i++)
    {
        guns[23].reload.frame_pos[i]=0.1;
        guns[23].left_reload.frame_pos[i]=0.1;
        guns[23].right_reload.frame_pos[i]=0.1;
    }
    for (int i=8; i<16; i++)
    {
        guns[23].reload.frame_pos[i]=1.1;
        guns[23].left_reload.frame_pos[i]=0.1;
        guns[23].right_reload.frame_pos[i]=1.1;
    }
    for (int i=16; i<24; i++)
    {
        guns[23].reload.frame_pos[i]=2.1;
        guns[23].left_reload.frame_pos[i]=0.1;
        guns[23].right_reload.frame_pos[i]=2.1;
    }
    for (int i=24; i<32; i++)
    {
        guns[23].reload.frame_pos[i]=1.1;
        guns[23].left_reload.frame_pos[i]=0.1;
        guns[23].right_reload.frame_pos[i]=1.1;
    }
    for (int i=32; i<41; i++)
    {
        guns[23].reload.frame_pos[i]=0.1;
        guns[23].left_reload.frame_pos[i]=0.1;
        guns[23].right_reload.frame_pos[i]=0.1;
    }


    guns[23].buffer.loadFromFile("Sounds/guns/23/0.wav");
    guns[23].sound.setBuffer(guns[23].buffer);

    guns[23].reload_buffer.loadFromFile("Sounds/guns/23/reload0.wav");
    guns[23].reload_sound.setBuffer(guns[23].reload_buffer);

    guns[23].bullet_texture.loadFromFile("Textures/electricity.png");
    guns[23].bullet.setTexture(guns[23].bullet_texture);
    guns[23].bullet.setTextureRect(IntRect(0, 0, 1, 3));

//guns[20


    guns[24].name="Railgun";
    guns[24].cat=0;
    guns[24].x=600;
    guns[24].y=250;
    //guns[17].radius=25;
    guns[24].ammo_used=0;
    //guns[24].proj_acceleration=-2;
    //guns[17].max_distance=600;
    //guns[17].self_explosion_knockback=0;
    //guns[17].explosion_knockback=0;
    //guns[17].self_damage_multiplier=0;
    //guns[17].splash_multiplier=1;
    guns[24].icon_texture.loadFromFile("Textures/guns/24/icon0.png");
    guns[24].icon.setTexture(guns[24].icon_texture);
    guns[24].damage=144;
    //guns[24].proj_speed=50;
    guns[24].knockback=6;
    //guns[24].spread=6;
    guns[24].create(1, 180, 20, 1);
    guns[24].max_load=0;
    guns[24].max_ammo=0;
    guns[24].isPistol=false;
    guns[24].pre.create(1, 200, 200, 100, 100, 1);
    guns[24].pre.fill_frames("Textures/guns/24/gun", 1);
    guns[24].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[24].left_pre.fill_frames("Textures/guns/24/left", 1);
    guns[24].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[24].right_pre.fill_frames("Textures/guns/24/right", 1);
    guns[24].animation.create(3, 200, 200, 100, 100, 0.1);
    guns[24].animation.fill_frames("Textures/guns/24/gun", 1);
    guns[24].left.create(2, 100, 100, 50, 50, 0.1);
    guns[24].left.fill_frames("Textures/guns/24/left", 1);
    guns[24].right.create(5, 100, 100, 50, 50, 0.1);
    guns[24].right.fill_frames("Textures/guns/24/right", 1);

    /*guns[16].reload.create(4, 200, 200, 100, 100, 0.1);
    guns[16].reload.fill_frames("Textures/guns/16/reload", 1);
    guns[16].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[16].left_reload.fill_frames("Textures/guns/16/left", 1);
    guns[16].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[16].right_reload.fill_frames("Textures/guns/16/right_reload", 1);*/

    guns[24].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[24].crosshair.fill_frames("Textures/guns/24/crosshair", 1);
    //guns[17].isProjectile=true;
    //guns[17].projectile.create(3, 100, 40, 0, 20, 0.1);
    //guns[17].projectile.fill_frames("Textures/guns/17/projectile", 1);

    //guns[17].blast.create(3, 50, 100, 25, 50, 0.15);
    //guns[17].blast.fill_frames("Textures/guns/17/blast", 1);

    /*guns[17].max_projectile_time=15;
    guns[17].blast.frame_pos=new double[16];
    guns[17].blast.f_count=16;
//setPR
    for (int i=0; i<5; i++)
    {
        guns[17].blast.frame_pos[i]=2.1;
    }

    for (int i=5; i<10; i++)
    {
        guns[17].blast.frame_pos[i]=1.1;
    }

    for (int i=10; i<16; i++)
    {
        guns[17].blast.frame_pos[i]=0.1;
    }

    guns[17].projectile.frame_pos=new double[20];
    guns[17].projectile.f_count=20;

    for (int i=0; i<4; i++)
    {
        guns[17].projectile.frame_pos[i]=2.1;
    }
    for (int i=4; i<7; i++)
    {
        guns[17].projectile.frame_pos[i]=1.1;
    }
    for (int i=7; i<21; i++)
    {
        guns[17].projectile.frame_pos[i]=0.1;
    }*/


    //guns[6].




    for (int i=0; i<30; i++)
    {
        guns[24].animation.frame_pos[i]=0.5;
        guns[24].left.frame_pos[i]=0.5;
        guns[24].right.frame_pos[i]=0.5;
        guns[24].crosshair.frame_pos[i]=0.5;
    }
    for (int i=30; i<60; i++)
    {
        guns[24].animation.frame_pos[i]=2.5;
        guns[24].left.frame_pos[i]=0.5;
        guns[24].right.frame_pos[i]=4.5;
        guns[24].crosshair.frame_pos[i]=0.5;
    }
    for (int i=60; i<90; i++)
    {
        guns[24].animation.frame_pos[i]=2.5;
        guns[24].left.frame_pos[i]=0.5;
        guns[24].right.frame_pos[i]=3.5;
        guns[24].crosshair.frame_pos[i]=0.5;
    }
    for (int i=90; i<120; i++)
    {
        guns[24].animation.frame_pos[i]=2.5;
        guns[24].left.frame_pos[i]=0.5;
        guns[24].right.frame_pos[i]=2.5;
        guns[24].crosshair.frame_pos[i]=0.5;
    }
    for (int i=120; i<150; i++)
    {
        guns[24].animation.frame_pos[i]=2.5;
        guns[24].left.frame_pos[i]=0.5;
        guns[24].right.frame_pos[i]=0.5;
        guns[24].crosshair.frame_pos[i]=1.5;
    }
    for (int i=150; i<181; i++)
    {
        guns[24].animation.frame_pos[i]=1.5;
        guns[24].left.frame_pos[i]=1.5;
        guns[24].right.frame_pos[i]=1.5;
        guns[24].crosshair.frame_pos[i]=1.5;
    }



    guns[24].pre.frame_pos[0]=0.1;
    guns[24].left_pre.frame_pos[0]=0.1;
    guns[24].right_pre.frame_pos[0]=0.1;


    guns[24].pre.frame_pos[1]=0.1;
    guns[24].left_pre.frame_pos[1]=0.1;
    guns[24].right_pre.frame_pos[1]=0.1;




    /*for (int i=0; i<12; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=48; i<60; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=60; i<72; i++)
    {
        guns[14].reload.frame_pos[i]=4.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=5.1;
    }
    for (int i=72; i<84; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=84; i<96; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=96; i<108; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=108; i<120; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=120; i<133; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }*/



    guns[24].buffer.loadFromFile("Sounds/guns/24/0.wav");
    guns[24].sound.setBuffer(guns[24].buffer);

    guns[24].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[24].bullet.setTexture(guns[24].bullet_texture);
    guns[24].bullet.setTextureRect(IntRect(0, 0, 1, 2));



    //guns[24].exp_buffer.loadFromFile("Sounds/guns/24/0.wav");


    guns[25].name="The Zapper";
    guns[25].cat=2;
    guns[25].x=600;
    guns[25].y=250;
    guns[25].radius=25;
    guns[25].max_distance=300;
    guns[25].self_explosion_knockback=0;
    guns[25].explosion_knockback=0;
    guns[25].self_damage_multiplier=0;
    guns[25].knockback=0;
    guns[25].splash_multiplier=1;
    guns[25].icon_texture.loadFromFile("Textures/guns/25/icon0.png");
    guns[25].icon.setTexture(guns[25].icon_texture);
    guns[25].damage=10;
    guns[25].proj_speed=100;
    guns[25].spread=2;
    guns[25].create(1, 2, 15, 70);
    guns[25].max_load=70;
    guns[25].max_ammo=70;
    guns[25].isPistol=false;
    guns[25].pre.create(1, 200, 200, 100, 100, 1);
    guns[25].pre.fill_frames("Textures/guns/25/gun", 1);
    guns[25].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[25].left_pre.fill_frames("Textures/guns/25/left", 1);
    guns[25].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[25].right_pre.fill_frames("Textures/guns/25/right", 1);
    guns[25].animation.create(1, 200, 200, 100, 100, 0.1);
    guns[25].animation.fill_frames("Textures/guns/25/gun", 1);
    guns[25].left.create(1, 100, 100, 50, 50, 0.1);
    guns[25].left.fill_frames("Textures/guns/25/left", 1);
    guns[25].right.create(1, 100, 100, 50, 50, 0.1);
    guns[25].right.fill_frames("Textures/guns/25/right", 1);

    guns[25].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[25].reload.fill_frames("Textures/guns/25/reload", 1);
    guns[25].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[25].left_reload.fill_frames("Textures/guns/25/left", 1);
    guns[25].right_reload.create(3, 100, 100, 50, 50, 0.1);
    guns[25].right_reload.fill_frames("Textures/guns/25/right_reload", 1);

    guns[25].crosshair.create(1, 200, 200, 100, 100, 0.1);
    guns[25].crosshair.fill_frames("Textures/guns/25/crosshair", 1);
    guns[25].isProjectile=true;
    guns[25].projectile.create(1, 100, 20, 50, 10, 0.1);
    guns[25].projectile.fill_frames("Textures/guns/25/projectile", 1);

    guns[25].blast.create(2, 20, 20, 10, 10, 0.15);
    guns[25].blast.fill_frames("Textures/guns/25/blast", 1);

    guns[25].max_projectile_time=15;
    guns[25].blast.frame_pos=new double[16];
    guns[25].blast.f_count=16;
//setPR
    for (int i=0; i<8; i++)
    {
        guns[25].blast.frame_pos[i]=1.1;
    }

    for (int i=8; i<16; i++)
    {
        guns[25].blast.frame_pos[i]=0.1;
    }



    guns[25].projectile.frame_pos=new double[4];
    guns[25].projectile.f_count=4;

    for (int i=0; i<4; i++)
    {
        guns[25].projectile.frame_pos[i]=0.1;
    }


    //guns[6].


    for (int i=0; i<2; i++)
    {
        guns[25].animation.frame_pos[i]=0.5;
        guns[25].left.frame_pos[i]=0.5;
        guns[25].right.frame_pos[i]=0.5;
        guns[25].crosshair.frame_pos[i]=0.5;
    }




    guns[25].pre.frame_pos[0]=0.1;
    guns[25].left_pre.frame_pos[0]=0.1;
    guns[25].right_pre.frame_pos[0]=0.1;


    guns[25].pre.frame_pos[1]=0.1;
    guns[25].left_pre.frame_pos[1]=0.1;
    guns[25].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<14; i++)
    {
        guns[25].reload.frame_pos[i]=0.1;
        guns[25].left_reload.frame_pos[i]=0.1;
        guns[25].right_reload.frame_pos[i]=0.1;
    }
    for (int i=14; i<28; i++)
    {
        guns[25].reload.frame_pos[i]=1.1;
        guns[25].left_reload.frame_pos[i]=0.1;
        guns[25].right_reload.frame_pos[i]=1.1;
    }
    for (int i=28; i<42; i++)
    {
        guns[25].reload.frame_pos[i]=2.1;
        guns[25].left_reload.frame_pos[i]=0.1;
        guns[25].right_reload.frame_pos[i]=2.1;
    }
    for (int i=42; i<56; i++)
    {
        guns[25].reload.frame_pos[i]=1.1;
        guns[25].left_reload.frame_pos[i]=0.1;
        guns[25].right_reload.frame_pos[i]=1.1;
    }
    for (int i=56; i<71; i++)
    {
        guns[25].reload.frame_pos[i]=0.1;
        guns[25].left_reload.frame_pos[i]=0.1;
        guns[25].right_reload.frame_pos[i]=0.1;
    }


    /*for (int i=0; i<12; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=48; i<60; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=60; i<72; i++)
    {
        guns[14].reload.frame_pos[i]=4.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=5.1;
    }
    for (int i=72; i<84; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=84; i<96; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=96; i<108; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=108; i<120; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=120; i<133; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }*/



    guns[25].buffer.loadFromFile("Sounds/guns/25/0.wav");
    guns[25].sound.setBuffer(guns[25].buffer);

    guns[25].reload_buffer.loadFromFile("Sounds/guns/25/reload0.wav");
    guns[25].reload_sound.setBuffer(guns[25].reload_buffer);

    guns[25].exp_buffer.loadFromFile("Sounds/guns/25/0.wav");

    guns[26].name="Golden Pistol";
    guns[26].cat=1;
    guns[26].x=600;
    guns[26].y=250;
    guns[26].icon_texture.loadFromFile("Textures/guns/26/icon0.png");
    guns[26].icon.setTexture(guns[26].icon_texture);
    guns[26].damage=60;
    guns[26].spread=0;
    guns[26].create(1, 45, 10, 60);
    guns[26].max_load=7;
    guns[26].max_ammo=7;
    guns[26].isPistol=true;
    guns[26].pre.create(1, 200, 200, 100, 100, 1);
    guns[26].pre.fill_frames("Textures/guns/26/gun", 1);
    guns[26].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[26].left_pre.fill_frames("Textures/guns/26/left", 1);
    guns[26].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[26].right_pre.fill_frames("Textures/guns/26/right", 1);
    guns[26].animation.create(3, 200, 200, 100, 100, 0.1);
    guns[26].animation.fill_frames("Textures/guns/26/gun", 1);
    guns[26].left.create(2, 100, 100, 50, 50, 0.1);
    guns[26].left.fill_frames("Textures/guns/26/left", 1);
    guns[26].right.create(1, 100, 100, 50, 50, 0.1);
    guns[26].right.fill_frames("Textures/guns/26/right", 1);
    guns[26].reload.create(2, 200, 200, 100, 100, 0.1);
    guns[26].reload.fill_frames("Textures/guns/26/reload", 1);
    guns[26].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[26].left_reload.fill_frames("Textures/guns/26/left", 1);
    guns[26].right_reload.create(3, 100, 100, 50, 50, 0.1);
    guns[26].right_reload.fill_frames("Textures/guns/26/right_reload", 1);
    guns[26].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[26].crosshair.fill_frames("Textures/guns/26/crosshair", 1);


    for (int i=0; i<15; i++)
    {
        guns[26].animation.frame_pos[i]=0.5;
        guns[26].left.frame_pos[i]=0.5;
        guns[26].right.frame_pos[i]=0.5;
        guns[26].crosshair.frame_pos[i]=0.5;
    }
    for (int i=15; i<30; i++)
    {//setFrame
        guns[26].animation.frame_pos[i]=2.5;
        guns[26].left.frame_pos[i]=0.5;
        guns[26].right.frame_pos[i]=0.5;
        guns[26].crosshair.frame_pos[i]=0.5;
    }

    for (int i=30; i<46; i++)
    {
        guns[26].animation.frame_pos[i]=1.5;
        guns[26].left.frame_pos[i]=1.5;
        guns[26].right.frame_pos[i]=0.5;
        guns[26].crosshair.frame_pos[i]=1.5;
    }

    guns[26].pre.frame_pos[0]=0.1;
    guns[26].left_pre.frame_pos[0]=0.1;
    guns[26].right_pre.frame_pos[0]=0.1;


    guns[26].pre.frame_pos[1]=0.1;
    guns[26].left_pre.frame_pos[1]=0.1;
    guns[26].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<12; i++)
    {
        guns[26].reload.frame_pos[i]=0.1;
        guns[26].left_reload.frame_pos[i]=0.1;
        guns[26].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[26].reload.frame_pos[i]=1.1;
        guns[26].left_reload.frame_pos[i]=0.1;
        guns[26].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[26].reload.frame_pos[i]=0.1;
        guns[26].left_reload.frame_pos[i]=0.1;
        guns[26].right_reload.frame_pos[i]=2.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[26].reload.frame_pos[i]=1.1;
        guns[26].left_reload.frame_pos[i]=0.1;
        guns[26].right_reload.frame_pos[i]=1.1;
    }
    for (int i=48; i<61; i++)
    {
        guns[26].reload.frame_pos[i]=0.1;
        guns[26].left_reload.frame_pos[i]=0.1;
        guns[26].right_reload.frame_pos[i]=0.1;
    }


    guns[26].buffer.loadFromFile("Sounds/guns/26/0.wav");
    guns[26].sound.setBuffer(guns[26].buffer);

    guns[26].reload_buffer.loadFromFile("Sounds/guns/26/reload0.wav");
    guns[26].reload_sound.setBuffer(guns[26].reload_buffer);

    guns[26].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[26].bullet.setTexture(guns[26].bullet_texture);
    guns[26].bullet.setTextureRect(IntRect(0, 0, 1, 2));




    guns[27].name="The Mounted Sentry";
    guns[27].cat=0;
    guns[27].x=750;
    guns[27].y=250;
    guns[27].knockback=5;
    guns[27].icon_texture.loadFromFile("Textures/guns/27/icon0.png");
    guns[27].icon.setTexture(guns[27].icon_texture);
    guns[27].damage=18;
    guns[27].spread=0;
    guns[27].create(1, 9, 10, 68);
    guns[27].max_load=30;
    guns[27].max_ammo=30;
    guns[27].isPistol=true;
    guns[27].pre.create(1, 200, 200, 100, 100, 1);
    guns[27].pre.fill_frames("Textures/guns/27/gun", 1);
    guns[27].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[27].left_pre.fill_frames("Textures/guns/27/left", 1);
    guns[27].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[27].right_pre.fill_frames("Textures/guns/27/right", 1);
    guns[27].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[27].animation.fill_frames("Textures/guns/27/gun", 1);
    guns[27].left.create(1, 100, 100, 50, 50, 0.1);
    guns[27].left.fill_frames("Textures/guns/27/left", 1);
    guns[27].right.create(1, 100, 100, 50, 50, 0.1);
    guns[27].right.fill_frames("Textures/guns/27/right", 1);
    guns[27].reload.create(4, 200, 200, 100, 100, 0.1);
    guns[27].reload.fill_frames("Textures/guns/27/reload", 1);
    guns[27].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[27].left_reload.fill_frames("Textures/guns/27/left", 1);
    guns[27].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[27].right_reload.fill_frames("Textures/guns/27/right_reload", 1);
    guns[27].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[27].crosshair.fill_frames("Textures/guns/27/crosshair", 1);


    for (int i=0; i<4; i++)
    {
        guns[27].animation.frame_pos[i]=0.5;
        guns[27].left.frame_pos[i]=0.5;
        guns[27].right.frame_pos[i]=0.5;
        guns[27].crosshair.frame_pos[i]=0.5;
    }
    for (int i=4; i<10; i++)
    {//setFrame
        guns[27].animation.frame_pos[i]=1.5;
        guns[27].left.frame_pos[i]=0.5;
        guns[27].right.frame_pos[i]=0.5;
        guns[27].crosshair.frame_pos[i]=1.5;
    }

    guns[27].pre.frame_pos[0]=0.1;
    guns[27].left_pre.frame_pos[0]=0.1;
    guns[27].right_pre.frame_pos[0]=0.1;


    guns[27].pre.frame_pos[1]=0.1;
    guns[27].left_pre.frame_pos[1]=0.1;
    guns[27].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<8; i++)
    {
        guns[27].reload.frame_pos[i]=0.1;
        guns[27].left_reload.frame_pos[i]=0.1;
        guns[27].right_reload.frame_pos[i]=3.1;
    }
    for (int i=8; i<16; i++)
    {
        guns[27].reload.frame_pos[i]=3.1;
        guns[27].left_reload.frame_pos[i]=0.1;
        guns[27].right_reload.frame_pos[i]=4.1;
    }
    for (int i=16; i<24; i++)
    {
        guns[27].reload.frame_pos[i]=0.1;
        guns[27].left_reload.frame_pos[i]=0.1;
        guns[27].right_reload.frame_pos[i]=3.1;
    }
    for (int i=24; i<34; i++)
    {
        guns[27].reload.frame_pos[i]=0.1;
        guns[27].left_reload.frame_pos[i]=0.1;
        guns[27].right_reload.frame_pos[i]=0.1;
    }
    for (int i=34; i<42; i++)
    {
        guns[27].reload.frame_pos[i]=1.1;
        guns[27].left_reload.frame_pos[i]=0.1;
        guns[27].right_reload.frame_pos[i]=1.1;
    }
    for (int i=42; i<52; i++)
    {
        guns[27].reload.frame_pos[i]=2.1;
        guns[27].left_reload.frame_pos[i]=0.1;
        guns[27].right_reload.frame_pos[i]=2.1;
    }
    for (int i=52; i<60; i++)
    {
        guns[27].reload.frame_pos[i]=1.1;
        guns[27].left_reload.frame_pos[i]=0.1;
        guns[27].right_reload.frame_pos[i]=1.1;
    }
    for (int i=60; i<69; i++)
    {
        guns[27].reload.frame_pos[i]=0.1;
        guns[27].left_reload.frame_pos[i]=0.1;
        guns[27].right_reload.frame_pos[i]=0.1;
    }

    guns[27].buffer.loadFromFile("Sounds/guns/27/0.wav");
    guns[27].sound.setBuffer(guns[27].buffer);

    guns[27].reload_buffer.loadFromFile("Sounds/guns/27/reload0.wav");
    guns[27].reload_sound.setBuffer(guns[27].reload_buffer);

    guns[27].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[27].bullet.setTexture(guns[27].bullet_texture);
    guns[27].bullet.setTextureRect(IntRect(0, 0, 1, 2));

    guns[28].name="Shotgun Uzi";
    guns[28].cat=1;
    guns[28].x=750;
    guns[28].y=250;
    guns[28].knockback=1;
    guns[28].pellets=1;
    guns[28].pellet_spread=0.03;
    guns[28].icon_texture.loadFromFile("Textures/guns/28/icon0.png");
    guns[28].icon.setTexture(guns[28].icon_texture);
    guns[28].damage=4;
    guns[28].spread=3;
    guns[28].create(1, 6, 10, 48);
    guns[28].max_load=30;
    guns[28].max_ammo=30;
    guns[28].isPistol=true;
    guns[28].pre.create(1, 200, 200, 100, 100, 1);
    guns[28].pre.fill_frames("Textures/guns/28/gun", 1);
    guns[28].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[28].left_pre.fill_frames("Textures/guns/28/left", 1);
    guns[28].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[28].right_pre.fill_frames("Textures/guns/28/right", 1);
    guns[28].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[28].animation.fill_frames("Textures/guns/28/gun", 1);
    guns[28].left.create(1, 100, 100, 50, 50, 0.1);
    guns[28].left.fill_frames("Textures/guns/28/left", 1);
    guns[28].right.create(1, 100, 100, 50, 50, 0.1);
    guns[28].right.fill_frames("Textures/guns/28/right", 1);
    guns[28].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[28].reload.fill_frames("Textures/guns/28/reload", 1);
    guns[28].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[28].left_reload.fill_frames("Textures/guns/28/left", 1);
    guns[28].right_reload.create(4, 100, 100, 50, 50, 0.1);
    guns[28].right_reload.fill_frames("Textures/guns/28/right_reload", 1);
    guns[28].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[28].crosshair.fill_frames("Textures/guns/28/crosshair", 1);


    for (int i=0; i<3; i++)
    {
        guns[28].animation.frame_pos[i]=0.5;
        guns[28].left.frame_pos[i]=0.5;
        guns[28].right.frame_pos[i]=0.5;
        guns[28].crosshair.frame_pos[i]=0.5;
    }
    for (int i=3; i<7; i++)
    {//setFrame
        guns[28].animation.frame_pos[i]=1.5;
        guns[28].left.frame_pos[i]=0.5;
        guns[28].right.frame_pos[i]=0.5;
        guns[28].crosshair.frame_pos[i]=1.5;
    }



    guns[28].pre.frame_pos[0]=0.1;
    guns[28].left_pre.frame_pos[0]=0.1;
    guns[28].right_pre.frame_pos[0]=0.1;


    guns[28].pre.frame_pos[1]=0.1;
    guns[28].left_pre.frame_pos[1]=0.1;
    guns[28].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<8; i++)
    {
        guns[28].reload.frame_pos[i]=0.1;
        guns[28].left_reload.frame_pos[i]=0.1;
        guns[28].right_reload.frame_pos[i]=3.1;
    }
    for (int i=8; i<16; i++)
    {
        guns[28].reload.frame_pos[i]=0.1;
        guns[28].left_reload.frame_pos[i]=0.1;
        guns[28].right_reload.frame_pos[i]=0.1;
    }
    for (int i=16; i<24; i++)
    {
        guns[28].reload.frame_pos[i]=1.1;
        guns[28].left_reload.frame_pos[i]=0.1;
        guns[28].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<32; i++)
    {
        guns[28].reload.frame_pos[i]=2.1;
        guns[28].left_reload.frame_pos[i]=0.1;
        guns[28].right_reload.frame_pos[i]=2.1;
    }
    for (int i=32; i<40; i++)
    {
        guns[28].reload.frame_pos[i]=1.1;
        guns[28].left_reload.frame_pos[i]=0.1;
        guns[28].right_reload.frame_pos[i]=1.1;
    }
    for (int i=40; i<49; i++)
    {
        guns[28].reload.frame_pos[i]=0.1;
        guns[28].left_reload.frame_pos[i]=0.1;
        guns[28].right_reload.frame_pos[i]=0.1;
    }


    guns[28].buffer.loadFromFile("Sounds/guns/28/0.wav");
    guns[28].sound.setBuffer(guns[28].buffer);

    guns[28].reload_buffer.loadFromFile("Sounds/guns/28/reload0.wav");
    guns[28].reload_sound.setBuffer(guns[28].reload_buffer);

    guns[28].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[28].bullet.setTexture(guns[28].bullet_texture);
    guns[28].bullet.setTextureRect(IntRect(0, 0, 1, 2));




    guns[29].name="Boosty & Speedy";
    guns[29].cat=1;
    guns[29].x=900;
    guns[29].y=250;
    //guns[17].radius=25;
    guns[29].ammo_used=0;
    //guns[24].proj_acceleration=-2;
    //guns[17].max_distance=600;
    //guns[17].self_explosion_knockback=0;
    //guns[17].explosion_knockback=0;
    //guns[17].self_damage_multiplier=0;
    //guns[17].splash_multiplier=1;
    guns[29].icon_texture.loadFromFile("Textures/guns/29/icon0.png");
    guns[29].icon.setTexture(guns[29].icon_texture);
    guns[29].damage=5;
    //guns[24].proj_speed=50;
    guns[29].knockback=1;
    //guns[24].spread=6;
    guns[29].create(1, 3, 10, 1);
    guns[29].max_load=0;
    guns[29].max_ammo=0;
    guns[29].isPistol=false;
    guns[29].pre.create(1, 200, 200, 100, 100, 1);
    guns[29].pre.fill_frames("Textures/guns/29/gun", 1);
    guns[29].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[29].left_pre.fill_frames("Textures/guns/29/left", 1);
    guns[29].right_pre.create(1, 200, 200, 100, 100, 1);
    guns[29].right_pre.fill_frames("Textures/guns/29/right", 1);
    guns[29].animation.create(1, 200, 200, 100, 100, 0.1);
    guns[29].animation.fill_frames("Textures/guns/29/gun", 1);
    guns[29].left.create(1, 100, 100, 50, 50, 0.1);
    guns[29].left.fill_frames("Textures/guns/29/left", 1);
    guns[29].right.create(1, 200, 200, 100, 100, 0.1);
    guns[29].right.fill_frames("Textures/guns/29/right", 1);

    /*guns[16].reload.create(4, 200, 200, 100, 100, 0.1);
    guns[16].reload.fill_frames("Textures/guns/16/reload", 1);
    guns[16].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[16].left_reload.fill_frames("Textures/guns/16/left", 1);
    guns[16].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[16].right_reload.fill_frames("Textures/guns/16/right_reload", 1);*/

    guns[29].crosshair.create(1, 200, 200, 100, 100, 0.1);
    guns[29].crosshair.fill_frames("Textures/guns/29/crosshair", 1);
    //guns[17].isProjectile=true;
    //guns[17].projectile.create(3, 100, 40, 0, 20, 0.1);
    //guns[17].projectile.fill_frames("Textures/guns/17/projectile", 1);

    //guns[17].blast.create(3, 50, 100, 25, 50, 0.15);
    //guns[17].blast.fill_frames("Textures/guns/17/blast", 1);

    /*guns[17].max_projectile_time=15;
    guns[17].blast.frame_pos=new double[16];
    guns[17].blast.f_count=16;
//setPR
    for (int i=0; i<5; i++)
    {
        guns[17].blast.frame_pos[i]=2.1;
    }

    for (int i=5; i<10; i++)
    {
        guns[17].blast.frame_pos[i]=1.1;
    }

    for (int i=10; i<16; i++)
    {
        guns[17].blast.frame_pos[i]=0.1;
    }

    guns[17].projectile.frame_pos=new double[20];
    guns[17].projectile.f_count=20;

    for (int i=0; i<4; i++)
    {
        guns[17].projectile.frame_pos[i]=2.1;
    }
    for (int i=4; i<7; i++)
    {
        guns[17].projectile.frame_pos[i]=1.1;
    }
    for (int i=7; i<21; i++)
    {
        guns[17].projectile.frame_pos[i]=0.1;
    }*/


    //guns[6].




    for (int i=0; i<4; i++)
    {
        guns[29].animation.frame_pos[i]=0.5;
        guns[29].left.frame_pos[i]=0.5;
        guns[29].right.frame_pos[i]=0.5;
        guns[29].crosshair.frame_pos[i]=0.5;
    }




    guns[29].pre.frame_pos[0]=0.1;
    guns[29].left_pre.frame_pos[0]=0.1;
    guns[29].right_pre.frame_pos[0]=0.1;


    guns[29].pre.frame_pos[1]=0.1;
    guns[29].left_pre.frame_pos[1]=0.1;
    guns[29].right_pre.frame_pos[1]=0.1;




    /*for (int i=0; i<12; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=48; i<60; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=60; i<72; i++)
    {
        guns[14].reload.frame_pos[i]=4.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=5.1;
    }
    for (int i=72; i<84; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=84; i<96; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=96; i<108; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=108; i<120; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=120; i<133; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }*/



    guns[29].buffer.loadFromFile("Sounds/guns/29/0.wav");
    guns[29].sound.setBuffer(guns[29].buffer);



    guns[29].exp_buffer.loadFromFile("Sounds/guns/29/0.wav");

    guns[29].bullet_texture.loadFromFile("Textures/blue_laser.png");
    guns[29].bullet.setTexture(guns[29].bullet_texture);
    guns[29].bullet.setTextureRect(IntRect(0, 0, 1, 2));


    guns[30].name="Plasma Shotgun";
    guns[30].cat=2;
    guns[30].pellets=2;
    guns[30].pellet_spread=0.02;
    guns[30].x=750;
    guns[30].y=250;
    guns[30].radius=25;
    guns[30].self_explosion_knockback=0;
    guns[30].explosion_knockback=0;
    guns[30].self_damage_multiplier=0;
    guns[30].splash_multiplier=2;
    guns[30].icon_texture.loadFromFile("Textures/guns/30/icon0.png");
    guns[30].icon.setTexture(guns[30].icon_texture);
    guns[30].damage=15;
    guns[30].proj_speed=150;
    guns[30].spread=0;
    guns[30].create(1, 65, 20, 84);
    guns[30].max_load=8;
    guns[30].max_ammo=8;
    guns[30].isPistol=false;
    guns[30].pre.create(1, 200, 200, 100, 100, 1);
    guns[30].pre.fill_frames("Textures/guns/30/gun", 1);
    guns[30].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[30].left_pre.fill_frames("Textures/guns/30/left", 1);
    guns[30].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[30].right_pre.fill_frames("Textures/guns/30/right", 1);
    guns[30].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[30].animation.fill_frames("Textures/guns/30/gun", 1);
    guns[30].left.create(2, 100, 100, 50, 50, 0.1);
    guns[30].left.fill_frames("Textures/guns/30/left", 1);
    guns[30].right.create(2, 100, 100, 50, 50, 0.1);
    guns[30].right.fill_frames("Textures/guns/30/right", 1);

    guns[30].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[30].reload.fill_frames("Textures/guns/30/reload", 1);
    guns[30].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[30].left_reload.fill_frames("Textures/guns/30/left", 1);
    guns[30].right_reload.create(4, 100, 100, 50, 50, 0.1);
    guns[30].right_reload.fill_frames("Textures/guns/30/right_reload", 1);

    guns[30].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[30].crosshair.fill_frames("Textures/guns/30/crosshair", 1);
    guns[30].isProjectile=true;
    guns[30].projectile.create(1, 20, 12, 20, 6, 0.1);
    guns[30].projectile.fill_frames("Textures/guns/30/projectile", 1);

    guns[30].blast.create(3, 50, 50, 25, 25, 0.15);
    guns[30].blast.fill_frames("Textures/guns/30/blast", 1);

    guns[30].max_projectile_time=15;
    guns[30].blast.frame_pos=new double[16];
    guns[30].blast.f_count=16;
//setPR
    for (int i=0; i<5; i++)
    {
        guns[30].blast.frame_pos[i]=2.1;
    }

    for (int i=5; i<10; i++)
    {
        guns[30].blast.frame_pos[i]=1.1;
    }

    for (int i=10; i<16; i++)
    {
        guns[30].blast.frame_pos[i]=0.1;
    }

    guns[30].projectile.frame_pos=new double[9];
    guns[30].projectile.f_count=9;

    for (int i=0; i<9; i++)
    {
        guns[30].projectile.frame_pos[i]=0.1;
    }


    //guns[6].


    for (int i=0; i<40; i++)
    {
        guns[30].animation.frame_pos[i]=0.5;
        guns[30].left.frame_pos[i]=0.5;
        guns[30].right.frame_pos[i]=0.5;
        guns[30].crosshair.frame_pos[i]=0.5;
    }
    for (int i=40; i<66; i++)
    {//setFrame
        guns[30].animation.frame_pos[i]=1.5;
        guns[30].left.frame_pos[i]=1.5;
        guns[30].right.frame_pos[i]=1.5;
        guns[30].crosshair.frame_pos[i]=1.5;
    }



    guns[30].pre.frame_pos[0]=0.1;
    guns[30].left_pre.frame_pos[0]=0.1;
    guns[30].right_pre.frame_pos[0]=0.1;


    guns[30].pre.frame_pos[1]=0.1;
    guns[30].left_pre.frame_pos[1]=0.1;
    guns[30].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<12; i++)
    {
        guns[30].reload.frame_pos[i]=0.1;
        guns[30].left_reload.frame_pos[i]=0.1;
        guns[30].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[30].reload.frame_pos[i]=0.1;
        guns[30].left_reload.frame_pos[i]=0.1;
        guns[30].right_reload.frame_pos[i]=3.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[30].reload.frame_pos[i]=0.1;
        guns[30].left_reload.frame_pos[i]=0.1;
        guns[30].right_reload.frame_pos[i]=0.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[30].reload.frame_pos[i]=1.1;
        guns[30].left_reload.frame_pos[i]=0.1;
        guns[30].right_reload.frame_pos[i]=1.1;
    }
    for (int i=48; i<60; i++)
    {
        guns[30].reload.frame_pos[i]=2.1;
        guns[30].left_reload.frame_pos[i]=0.1;
        guns[30].right_reload.frame_pos[i]=2.1;
    }
    for (int i=60; i<72; i++)
    {
        guns[30].reload.frame_pos[i]=1.1;
        guns[30].left_reload.frame_pos[i]=0.1;
        guns[30].right_reload.frame_pos[i]=1.1;
    }
    for (int i=72; i<85; i++)
    {
        guns[30].reload.frame_pos[i]=0.1;
        guns[30].left_reload.frame_pos[i]=0.1;
        guns[30].right_reload.frame_pos[i]=0.1;
    }

    /*for (int i=0; i<12; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=48; i<60; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=60; i<72; i++)
    {
        guns[14].reload.frame_pos[i]=4.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=5.1;
    }
    for (int i=72; i<84; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=84; i<96; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=96; i<108; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=108; i<120; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=120; i<133; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }*/



    guns[30].buffer.loadFromFile("Sounds/guns/30/0.wav");
    guns[30].sound.setBuffer(guns[30].buffer);

    guns[30].reload_buffer.loadFromFile("Sounds/guns/30/reload0.wav");
    guns[30].reload_sound.setBuffer(guns[30].reload_buffer);

    guns[30].exp_buffer.loadFromFile("Sounds/guns/30/explosion0.wav");




    guns[31].name="Rocket Launcher";
    guns[31].cat=2;
    guns[31].x=900;
    guns[31].y=250;
    guns[31].self_damage_multiplier=0.3;
    guns[31].self_explosion_knockback=150;
    guns[31].explosion_knockback=75;
    guns[31].radius=200;
    guns[31].splash_multiplier=1;
    guns[31].icon_texture.loadFromFile("Textures/guns/31/icon0.png");
    guns[31].icon.setTexture(guns[31].icon_texture);
    guns[31].damage=200;
    guns[31].proj_speed=75;
    guns[31].spread=0;
    guns[31].create(1, 20, 25, 150);
    guns[31].max_load=1;
    guns[31].max_ammo=1;
    guns[31].isPistol=true;
    guns[31].pre.create(1, 200, 200, 100, 100, 1);
    guns[31].pre.fill_frames("Textures/guns/31/gun", 1);
    guns[31].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[31].left_pre.fill_frames("Textures/guns/31/left", 1);
    guns[31].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[31].right_pre.fill_frames("Textures/guns/31/right", 1);
    guns[31].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[31].animation.fill_frames("Textures/guns/31/gun", 1);
    guns[31].left.create(1, 100, 100, 50, 50, 0.1);
    guns[31].left.fill_frames("Textures/guns/31/left", 1);
    guns[31].right.create(1, 100, 100, 50, 50, 0.1);
    guns[31].right.fill_frames("Textures/guns/31/right", 1);
    guns[31].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[31].reload.fill_frames("Textures/guns/31/reload", 1);
    guns[31].left_reload.create(2, 100, 100, 50, 50, 0.1);
    guns[31].left_reload.fill_frames("Textures/guns/31/left_reload", 1);
    guns[31].right_reload.create(3, 100, 100, 50, 50, 0.1);
    guns[31].right_reload.fill_frames("Textures/guns/31/right_reload", 1);
    guns[31].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[31].crosshair.fill_frames("Textures/guns/31/crosshair", 1);
    guns[31].isProjectile=true;
    guns[31].projectile.create(2, 100, 20, 50, 10, 0.1);
    guns[31].projectile.fill_frames("Textures/guns/31/projectile", 1);

    guns[31].blast.create(4, 400, 400, 200, 200, 0.15);
    guns[31].blast.fill_frames("Textures/guns/31/blast", 1);

    guns[31].max_projectile_time=24;
    guns[31].blast.frame_pos=new double[25];
    guns[31].blast.f_count=25;

    for (int i=0; i<6; i++)
    {
        guns[31].blast.frame_pos[i]=3.1;
    }

    for (int i=6; i<12; i++)
    {
        guns[31].blast.frame_pos[i]=2.1;
    }

    for (int i=12; i<18; i++)
    {
        guns[31].blast.frame_pos[i]=1.1;
    }
    for (int i=18; i<25; i++)
    {
        guns[31].blast.frame_pos[i]=0.1;
    }

    guns[31].projectile.frame_pos=new double[17];
    guns[31].projectile.f_count=17;


    for (int i=12; i<17; i++)
    {
        guns[31].projectile.frame_pos[i]=0.1;
    }
    for (int i=6; i<12; i++)
    {
        guns[31].projectile.frame_pos[i]=1.1;
    }
    for (int i=0; i<6; i++)
    {
        guns[31].projectile.frame_pos[i]=0.1;
    }

    //guns[6].



    guns[31].animation.frame_pos[0]=0.5;
        guns[31].left.frame_pos[0]=0.5;
        guns[31].right.frame_pos[0]=0.5;
        guns[31].crosshair.frame_pos[0]=0.5;

    for (int i=1; i<21; i++)
    {//setFrame
        guns[31].animation.frame_pos[i]=1.5;
        guns[31].left.frame_pos[i]=0.5;
        guns[31].right.frame_pos[i]=0.5;
        guns[31].crosshair.frame_pos[i]=1.5;
    }



    guns[31].pre.frame_pos[0]=0.1;
    guns[31].left_pre.frame_pos[0]=0.1;
    guns[31].right_pre.frame_pos[0]=0.1;


    guns[31].pre.frame_pos[1]=0.1;
    guns[31].left_pre.frame_pos[1]=0.1;
    guns[31].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<30; i++)
    {
        guns[31].reload.frame_pos[i]=2.1;
        guns[31].left_reload.frame_pos[i]=1.1;
        guns[31].right_reload.frame_pos[i]=0.1;
    }
    for (int i=30; i<70; i++)
    {
        guns[31].reload.frame_pos[i]=0.1;
        guns[31].left_reload.frame_pos[i]=0.1;
        guns[31].right_reload.frame_pos[i]=2.1;
    }
    for (int i=70; i<110; i++)
    {
        guns[31].reload.frame_pos[i]=1.1;
        guns[31].left_reload.frame_pos[i]=0.1;
        guns[31].right_reload.frame_pos[i]=1.1;
    }
    for (int i=110; i<151; i++)
    {
        guns[31].reload.frame_pos[i]=0.1;
        guns[31].left_reload.frame_pos[i]=0.1;
        guns[31].right_reload.frame_pos[i]=0.1;
    }



    guns[31].buffer.loadFromFile("Sounds/guns/31/0.wav");
    guns[31].sound.setBuffer(guns[31].buffer);

    guns[31].reload_buffer.loadFromFile("Sounds/guns/31/reload0.wav");
    guns[31].reload_sound.setBuffer(guns[31].reload_buffer);

    guns[31].exp_buffer.loadFromFile("Sounds/guns/31/explosion0.wav");


    guns[32].name="Tesla Rifle";
    guns[32].cat=2;
    guns[32].x=1050;
    guns[32].y=250;
    guns[32].self_damage_multiplier=0.2;
    guns[32].self_explosion_knockback=0;
    guns[32].explosion_knockback=0;
    guns[32].knockback=0;
    guns[32].radius=75;
    guns[32].splash_multiplier=1.8;
    guns[32].icon_texture.loadFromFile("Textures/guns/32/icon0.png");
    guns[32].icon.setTexture(guns[32].icon_texture);
    guns[32].damage=108;
    guns[32].proj_speed=1200;
    guns[32].spread=0;
    guns[32].create(1, 100, 15, 120);
    guns[32].max_load=7;
    guns[32].max_ammo=7;
    guns[32].isPistol=false;
    guns[32].pre.create(1, 200, 200, 100, 100, 1);
    guns[32].pre.fill_frames("Textures/guns/32/gun", 1);
    guns[32].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[32].left_pre.fill_frames("Textures/guns/32/left", 1);
    guns[32].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[32].right_pre.fill_frames("Textures/guns/32/right", 1);
    guns[32].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[32].animation.fill_frames("Textures/guns/32/gun", 1);
    guns[32].left.create(1, 100, 100, 50, 50, 0.1);
    guns[32].left.fill_frames("Textures/guns/32/left", 1);
    guns[32].right.create(1, 100, 100, 50, 50, 0.1);
    guns[32].right.fill_frames("Textures/guns/32/right", 1);
    guns[32].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[32].reload.fill_frames("Textures/guns/32/reload", 1);
    guns[32].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[32].left_reload.fill_frames("Textures/guns/32/left", 1);
    guns[32].right_reload.create(4, 100, 100, 50, 50, 0.1);
    guns[32].right_reload.fill_frames("Textures/guns/32/right_reload", 1);
    guns[32].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[32].crosshair.fill_frames("Textures/guns/32/crosshair", 1);
    guns[32].isProjectile=true;
    guns[32].projectile.create(1, 100, 20, 50, 10, 0.1);
    guns[32].projectile.fill_frames("Textures/", 1);

    guns[32].blast.create(2, 150, 150, 75, 75, 0.15);
    guns[32].blast.fill_frames("Textures/guns/32/blast", 1);

    guns[32].max_projectile_time=12;
    guns[32].blast.frame_pos=new double[13];
    guns[32].blast.f_count=13;

    for (int i=0; i<6; i++)
    {
        guns[32].blast.frame_pos[i]=1.1;
    }

    for (int i=6; i<13; i++)
    {
        guns[32].blast.frame_pos[i]=0.1;
    }



    guns[32].projectile.frame_pos=new double[1];
    guns[32].projectile.f_count=1;



        guns[32].projectile.frame_pos[0]=0.1;



    //guns[6].





    for (int i=0; i<50; i++)
    {//setFrame
        guns[32].animation.frame_pos[i]=0.5;
        guns[32].left.frame_pos[i]=0.5;
        guns[32].right.frame_pos[i]=0.5;
        guns[32].crosshair.frame_pos[i]=0.5;
    }
    for (int i=50; i<101; i++)
    {//setFrame
        guns[32].animation.frame_pos[i]=1.5;
        guns[32].left.frame_pos[i]=0.5;
        guns[32].right.frame_pos[i]=0.5;
        guns[32].crosshair.frame_pos[i]=1.5;
    }



    guns[32].pre.frame_pos[0]=0.1;
    guns[32].left_pre.frame_pos[0]=0.1;
    guns[32].right_pre.frame_pos[0]=0.1;


    guns[32].pre.frame_pos[1]=0.1;
    guns[32].left_pre.frame_pos[1]=0.1;
    guns[32].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<20; i++)
    {
        guns[32].reload.frame_pos[i]=0.1;
        guns[32].left_reload.frame_pos[i]=0.1;
        guns[32].right_reload.frame_pos[i]=3.1;
    }
    for (int i=20; i<40; i++)
    {
        guns[32].reload.frame_pos[i]=0.1;
        guns[32].left_reload.frame_pos[i]=0.1;
        guns[32].right_reload.frame_pos[i]=0.1;
    }
    for (int i=40; i<60; i++)
    {
        guns[32].reload.frame_pos[i]=1.1;
        guns[32].left_reload.frame_pos[i]=0.1;
        guns[32].right_reload.frame_pos[i]=1.1;
    }
    for (int i=60; i<80; i++)
    {
        guns[32].reload.frame_pos[i]=2.1;
        guns[32].left_reload.frame_pos[i]=0.1;
        guns[32].right_reload.frame_pos[i]=2.1;
    }
    for (int i=80; i<100; i++)
    {
        guns[32].reload.frame_pos[i]=1.1;
        guns[32].left_reload.frame_pos[i]=0.1;
        guns[32].right_reload.frame_pos[i]=1.1;
    }
    for (int i=100; i<121; i++)
    {
        guns[32].reload.frame_pos[i]=0.1;
        guns[32].left_reload.frame_pos[i]=0.1;
        guns[32].right_reload.frame_pos[i]=0.1;
    }



    guns[32].buffer.loadFromFile("Sounds/guns/32/0.wav");
    guns[32].sound.setBuffer(guns[32].buffer);

    guns[32].reload_buffer.loadFromFile("Sounds/guns/32/reload0.wav");
    guns[32].reload_sound.setBuffer(guns[32].reload_buffer);

    guns[32].exp_buffer.loadFromFile("Sounds/effects/0.wav");




    guns[33].name="Golden Gatling";
    guns[33].cat=2;
    guns[33].x=300;
    guns[33].y=400;
    guns[33].knockback=1;
    guns[33].ammo_used=0;
    guns[33].icon_texture.loadFromFile("Textures/guns/33/icon0.png");
    guns[33].icon.setTexture(guns[33].icon_texture);
    guns[33].damage=6;
    guns[33].spread=4;
    guns[33].create(1, 3, 20, 1);
    guns[33].max_load=0;
    guns[33].max_ammo=0;
    guns[33].isPistol=false;
    guns[33].pre.create(1, 200, 200, 100, 100, 1);
    guns[33].pre.fill_frames("Textures/guns/33/gun", 1);
    guns[33].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[33].left_pre.fill_frames("Textures/guns/33/left", 1);
    guns[33].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[33].right_pre.fill_frames("Textures/guns/33/right", 1);
    guns[33].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[33].animation.fill_frames("Textures/guns/33/gun", 1);
    guns[33].left.create(1, 100, 100, 50, 50, 0.1);
    guns[33].left.fill_frames("Textures/guns/33/left", 1);
    guns[33].right.create(1, 100, 100, 50, 50, 0.1);
    guns[33].right.fill_frames("Textures/guns/33/right", 1);

    guns[33].crosshair.create(1, 200, 200, 100, 100, 0.1);
    guns[33].crosshair.fill_frames("Textures/guns/33/crosshair", 1);




        guns[33].animation.frame_pos[0]=0.5;
        guns[33].left.frame_pos[0]=0.5;
        guns[33].right.frame_pos[0]=0.5;
        guns[33].crosshair.frame_pos[0]=0.5;


        guns[33].animation.frame_pos[1]=0.5;
        guns[33].left.frame_pos[1]=0.5;
        guns[33].right.frame_pos[1]=0.5;
        guns[33].crosshair.frame_pos[1]=0.5;

        guns[33].animation.frame_pos[2]=1.5;
        guns[33].left.frame_pos[2]=0.5;
        guns[33].right.frame_pos[2]=0.5;
        guns[33].crosshair.frame_pos[2]=0.5;

        guns[33].animation.frame_pos[3]=1.5;
        guns[33].left.frame_pos[3]=0.5;
        guns[33].right.frame_pos[3]=0.5;
        guns[33].crosshair.frame_pos[3]=0.5;



    guns[33].pre.frame_pos[0]=0.1;
    guns[33].left_pre.frame_pos[0]=0.1;
    guns[33].right_pre.frame_pos[0]=0.1;


    guns[33].pre.frame_pos[1]=0.1;
    guns[33].left_pre.frame_pos[1]=0.1;
    guns[33].right_pre.frame_pos[1]=0.1;




    guns[33].buffer.loadFromFile("Sounds/guns/33/0.wav");
    guns[33].sound.setBuffer(guns[33].buffer);



    guns[33].bullet_texture.loadFromFile("Textures/gatling_bullet.png");
    guns[33].bullet.setTexture(guns[33].bullet_texture);
    guns[33].bullet.setTextureRect(IntRect(0, 0, 1, 48));


    guns[34].name="The Knife";
    guns[34].cat=1;
    guns[34].x=1050;
    guns[34].y=250;
    guns[34].knockback=6;
    guns[34].ammo_used=0;
    guns[34].icon_texture.loadFromFile("Textures/guns/34/icon0.png");
    guns[34].icon.setTexture(guns[34].icon_texture);
    guns[34].damage=120;
    guns[34].spread=0;
    guns[34].create(1, 30, 5, 1);
    guns[34].max_load=0;
    guns[34].max_ammo=0;
    guns[34].isPistol=true;
    guns[34].pre.create(1, 200, 200, 100, 100, 1);
    guns[34].pre.fill_frames("Textures/guns/34/gun", 1);
    guns[34].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[34].left_pre.fill_frames("Textures/guns/34/left", 1);
    guns[34].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[34].right_pre.fill_frames("Textures/guns/34/right", 1);
    guns[34].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[34].animation.fill_frames("Textures/guns/34/gun", 1);
    guns[34].left.create(2, 100, 100, 50, 50, 0.1);
    guns[34].left.fill_frames("Textures/guns/34/left", 1);
    guns[34].right.create(1, 100, 100, 50, 50, 0.1);
    guns[34].right.fill_frames("Textures/guns/34/right", 1);

    guns[34].crosshair.create(1, 200, 200, 100, 100, 0.1);
    guns[34].crosshair.fill_frames("Textures/guns/34/crosshair", 1);



    for (int i=0; i<15; i++)
    {
        guns[34].animation.frame_pos[i]=0.5;
        guns[34].left.frame_pos[i]=0.5;
        guns[34].right.frame_pos[i]=0.5;
        guns[34].crosshair.frame_pos[i]=0.5;
    }
    for (int i=15; i<31; i++)
    {
        guns[34].animation.frame_pos[i]=1.5;
        guns[34].left.frame_pos[i]=1.5;
        guns[34].right.frame_pos[i]=0.5;
        guns[34].crosshair.frame_pos[i]=0.5;
    }








    guns[34].pre.frame_pos[0]=0.1;
    guns[34].left_pre.frame_pos[0]=0.1;
    guns[34].right_pre.frame_pos[0]=0.1;


    guns[34].pre.frame_pos[1]=0.1;
    guns[34].left_pre.frame_pos[1]=0.1;
    guns[34].right_pre.frame_pos[1]=0.1;




    guns[34].buffer.loadFromFile("Sounds/guns/34/0.wav");
    guns[34].sound.setBuffer(guns[34].buffer);



    guns[34].bullet_texture.loadFromFile("Textures/0.png");
    guns[34].bullet.setTexture(guns[34].bullet_texture);
    guns[34].bullet.setTextureRect(IntRect(0, 0, 1, 2));




    guns[35].name="Skeleton Musket";
    guns[35].cat=2;
    guns[35].x=450;
    guns[35].y=400;
    guns[35].knockback=2;
    guns[35].pellets=2;
    guns[35].pellet_spread=0.01;
    guns[35].icon_texture.loadFromFile("Textures/guns/35/icon0.png");
    guns[35].icon.setTexture(guns[35].icon_texture);
    guns[35].damage=12;
    guns[35].spread=0;
    guns[35].create(1, 40, 15, 70);
    guns[35].max_load=6;
    guns[35].max_ammo=6;
    guns[35].isPistol=false;
    guns[35].pre.create(1, 200, 200, 100, 100, 1);
    guns[35].pre.fill_frames("Textures/guns/35/gun", 1);
    guns[35].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[35].left_pre.fill_frames("Textures/guns/35/left", 1);
    guns[35].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[35].right_pre.fill_frames("Textures/guns/35/right", 1);
    guns[35].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[35].animation.fill_frames("Textures/guns/35/gun", 1);
    guns[35].left.create(2, 100, 100, 50, 50, 0.1);
    guns[35].left.fill_frames("Textures/guns/35/left", 1);
    guns[35].right.create(2, 100, 100, 50, 50, 0.1);
    guns[35].right.fill_frames("Textures/guns/35/right", 1);
    guns[35].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[35].reload.fill_frames("Textures/guns/35/reload", 1);
    guns[35].left_reload.create(2, 100, 100, 50, 50, 0.1);
    guns[35].left_reload.fill_frames("Textures/guns/35/left_reload", 1);
    guns[35].right_reload.create(5, 100, 100, 50, 50, 0.1);
    guns[35].right_reload.fill_frames("Textures/guns/35/right_reload", 1);
    guns[35].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[35].crosshair.fill_frames("Textures/guns/35/crosshair", 1);


    for (int i=0; i<20; i++)
    {
        guns[35].animation.frame_pos[i]=0.5;
        guns[35].left.frame_pos[i]=0.5;
        guns[35].right.frame_pos[i]=0.5;
        guns[35].crosshair.frame_pos[i]=0.5;
    }
    for (int i=20; i<41; i++)
    {//setFrame
        guns[35].animation.frame_pos[i]=1.5;
        guns[35].left.frame_pos[i]=1.5;
        guns[35].right.frame_pos[i]=1.5;
        guns[35].crosshair.frame_pos[i]=1.5;
    }



    guns[35].pre.frame_pos[0]=0.1;
    guns[35].left_pre.frame_pos[0]=0.1;
    guns[35].right_pre.frame_pos[0]=0.1;


    guns[35].pre.frame_pos[1]=0.1;
    guns[35].left_pre.frame_pos[1]=0.1;
    guns[35].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<14; i++)
    {
        guns[35].reload.frame_pos[i]=0.1;
        guns[35].left_reload.frame_pos[i]=0.1;
        guns[35].right_reload.frame_pos[i]=4.1;
    }
    for (int i=14; i<28; i++)
    {
        guns[35].reload.frame_pos[i]=2.1;
        guns[35].left_reload.frame_pos[i]=1.1;
        guns[35].right_reload.frame_pos[i]=3.1;
    }
    for (int i=28; i<42; i++)
    {
        guns[35].reload.frame_pos[i]=1.1;
        guns[35].left_reload.frame_pos[i]=0.1;
        guns[35].right_reload.frame_pos[i]=2.1;
    }
    for (int i=42; i<56; i++)
    {
        guns[35].reload.frame_pos[i]=1.1;
        guns[35].left_reload.frame_pos[i]=0.1;
        guns[35].right_reload.frame_pos[i]=1.1;
    }
    for (int i=56; i<71; i++)
    {
        guns[35].reload.frame_pos[i]=0.1;
        guns[35].left_reload.frame_pos[i]=0.1;
        guns[35].right_reload.frame_pos[i]=0.1;
    }



    guns[35].buffer.loadFromFile("Sounds/guns/35/0.wav");
    guns[35].sound.setBuffer(guns[35].buffer);

    guns[35].reload_buffer.loadFromFile("Sounds/guns/35/reload0.wav");
    guns[35].reload_sound.setBuffer(guns[35].reload_buffer);

    guns[35].bullet_texture.loadFromFile("Textures/blue_laser.png");
    guns[35].bullet.setTexture(guns[35].bullet_texture);
    guns[35].bullet.setTextureRect(IntRect(0, 0, 1, 2));


    guns[36].name="Rocket Shotgun";
    guns[36].knockback=1;
    guns[36].cat=2;
    guns[36].pellets=2;
    guns[36].pellet_spread=0.03;
    guns[36].x=600;
    guns[36].y=400;
    guns[36].radius=60;
    guns[36].self_explosion_knockback=6;
    guns[36].explosion_knockback=3;
    guns[36].self_damage_multiplier=0.1;
    guns[36].splash_multiplier=1.6;
    guns[36].icon_texture.loadFromFile("Textures/guns/36/icon0.png");
    guns[36].icon.setTexture(guns[36].icon_texture);
    guns[36].damage=12;
    guns[36].proj_speed=100;
    guns[36].spread=0;
    guns[36].create(1, 45, 20, 84);
    guns[36].max_load=5;
    guns[36].max_ammo=5;
    guns[36].isPistol=false;
    guns[36].pre.create(1, 200, 200, 100, 100, 1);
    guns[36].pre.fill_frames("Textures/guns/36/gun", 1);
    guns[36].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[36].left_pre.fill_frames("Textures/guns/36/left", 1);
    guns[36].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[36].right_pre.fill_frames("Textures/guns/36/right", 1);
    guns[36].animation.create(3, 200, 200, 100, 100, 0.1);
    guns[36].animation.fill_frames("Textures/guns/36/gun", 1);
    guns[36].left.create(2, 100, 100, 50, 50, 0.1);
    guns[36].left.fill_frames("Textures/guns/36/left", 1);
    guns[36].right.create(3, 100, 100, 50, 50, 0.1);
    guns[36].right.fill_frames("Textures/guns/36/right", 1);

    guns[36].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[36].reload.fill_frames("Textures/guns/36/reload", 1);
    guns[36].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[36].left_reload.fill_frames("Textures/guns/36/left", 1);
    guns[36].right_reload.create(4, 100, 100, 50, 50, 0.1);
    guns[36].right_reload.fill_frames("Textures/guns/36/right_reload", 1);

    guns[36].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[36].crosshair.fill_frames("Textures/guns/36/crosshair", 1);
    guns[36].isProjectile=true;
    guns[36].projectile.create(1, 50, 10, 25, 5, 0.1);
    guns[36].projectile.fill_frames("Textures/guns/36/projectile", 1);

    guns[36].blast.create(3, 120, 120, 60, 60, 0.15);
    guns[36].blast.fill_frames("Textures/guns/36/blast", 1);

    guns[36].max_projectile_time=15;
    guns[36].blast.frame_pos=new double[16];
    guns[36].blast.f_count=16;
//setPR
    for (int i=0; i<5; i++)
    {
        guns[36].blast.frame_pos[i]=2.1;
    }

    for (int i=5; i<10; i++)
    {
        guns[36].blast.frame_pos[i]=1.1;
    }

    for (int i=10; i<16; i++)
    {
        guns[36].blast.frame_pos[i]=0.1;
    }

    guns[36].projectile.frame_pos=new double[13];
    guns[36].projectile.f_count=13;

    for (int i=0; i<7; i++)
    {
        guns[36].projectile.frame_pos[i]=0.1;
    }
    for (int i=7; i<13; i++)
    {
        guns[36].projectile.frame_pos[i]=1.1;
    }



    //guns[6].


    for (int i=0; i<15; i++)
    {
        guns[36].animation.frame_pos[i]=0.5;
        guns[36].left.frame_pos[i]=0.5;
        guns[36].right.frame_pos[i]=0.5;
        guns[36].crosshair.frame_pos[i]=0.5;
    }
    for (int i=15; i<30; i++)
    {
        guns[36].animation.frame_pos[i]=2.5;
        guns[36].left.frame_pos[i]=0.5;
        guns[36].right.frame_pos[i]=2.5;
        guns[36].crosshair.frame_pos[i]=1.5;
    }
    for (int i=30; i<46; i++)
    {
        guns[36].animation.frame_pos[i]=1.5;
        guns[36].left.frame_pos[i]=1.5;
        guns[36].right.frame_pos[i]=1.5;
        guns[36].crosshair.frame_pos[i]=1.5;
    }



    guns[36].pre.frame_pos[0]=0.1;
    guns[36].left_pre.frame_pos[0]=0.1;
    guns[36].right_pre.frame_pos[0]=0.1;


    guns[36].pre.frame_pos[1]=0.1;
    guns[36].left_pre.frame_pos[1]=0.1;
    guns[36].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<12; i++)
    {
        guns[36].reload.frame_pos[i]=0.1;
        guns[36].left_reload.frame_pos[i]=0.1;
        guns[36].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[36].reload.frame_pos[i]=0.1;
        guns[36].left_reload.frame_pos[i]=0.1;
        guns[36].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[36].reload.frame_pos[i]=1.1;
        guns[36].left_reload.frame_pos[i]=0.1;
        guns[36].right_reload.frame_pos[i]=2.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[36].reload.frame_pos[i]=2.1;
        guns[36].left_reload.frame_pos[i]=0.1;
        guns[36].right_reload.frame_pos[i]=3.1;
    }
    for (int i=48; i<60; i++)
    {
        guns[36].reload.frame_pos[i]=1.1;
        guns[36].left_reload.frame_pos[i]=0.1;
        guns[36].right_reload.frame_pos[i]=2.1;
    }
    for (int i=60; i<72; i++)
    {
        guns[36].reload.frame_pos[i]=0.1;
        guns[36].left_reload.frame_pos[i]=0.1;
        guns[36].right_reload.frame_pos[i]=1.1;
    }
    for (int i=72; i<85; i++)
    {
        guns[36].reload.frame_pos[i]=0.1;
        guns[36].left_reload.frame_pos[i]=0.1;
        guns[36].right_reload.frame_pos[i]=0.1;
    }

    /*for (int i=0; i<12; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }
    for (int i=12; i<24; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<36; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=36; i<48; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=48; i<60; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=60; i<72; i++)
    {
        guns[14].reload.frame_pos[i]=4.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=5.1;
    }
    for (int i=72; i<84; i++)
    {
        guns[14].reload.frame_pos[i]=3.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=4.1;
    }
    for (int i=84; i<96; i++)
    {
        guns[14].reload.frame_pos[i]=2.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=3.1;
    }
    for (int i=96; i<108; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=2.1;
    }
    for (int i=108; i<120; i++)
    {
        guns[14].reload.frame_pos[i]=1.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=1.1;
    }
    for (int i=120; i<133; i++)
    {
        guns[14].reload.frame_pos[i]=0.1;
        guns[14].left_reload.frame_pos[i]=0.1;
        guns[14].right_reload.frame_pos[i]=0.1;
    }*/



    guns[36].buffer.loadFromFile("Sounds/guns/36/0.wav");
    guns[36].sound.setBuffer(guns[36].buffer);

    guns[36].reload_buffer.loadFromFile("Sounds/guns/36/reload0.wav");
    guns[36].reload_sound.setBuffer(guns[36].reload_buffer);

    guns[36].exp_buffer.loadFromFile("Sounds/guns/36/explosion0.wav");


    guns[37].name="Laser Uzi";
    guns[37].cat=1;
    guns[37].x=300;
    guns[37].y=400;
    guns[37].knockback=0;
    guns[37].icon_texture.loadFromFile("Textures/guns/37/icon0.png");
    guns[37].icon.setTexture(guns[37].icon_texture);
    guns[37].damage=10;
    guns[37].spread=0;
    guns[37].create(1, 5, 10, 48);
    guns[37].max_load=40;
    guns[37].max_ammo=40;
    guns[37].isPistol=true;
    guns[37].pre.create(1, 200, 200, 100, 100, 1);
    guns[37].pre.fill_frames("Textures/guns/37/gun", 1);
    guns[37].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[37].left_pre.fill_frames("Textures/guns/37/left", 1);
    guns[37].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[37].right_pre.fill_frames("Textures/guns/37/right", 1);
    guns[37].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[37].animation.fill_frames("Textures/guns/37/gun", 1);
    guns[37].left.create(1, 100, 100, 50, 50, 0.1);
    guns[37].left.fill_frames("Textures/guns/37/left", 1);
    guns[37].right.create(1, 100, 100, 50, 50, 0.1);
    guns[37].right.fill_frames("Textures/guns/37/right", 1);
    guns[37].reload.create(4, 200, 200, 100, 100, 0.1);
    guns[37].reload.fill_frames("Textures/guns/37/reload", 1);
    guns[37].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[37].left_reload.fill_frames("Textures/guns/37/left", 1);
    guns[37].right_reload.create(4, 100, 100, 50, 50, 0.1);
    guns[37].right_reload.fill_frames("Textures/guns/37/right_reload", 1);
    guns[37].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[37].crosshair.fill_frames("Textures/guns/37/crosshair", 1);


    for (int i=0; i<3; i++)
    {
        guns[37].animation.frame_pos[i]=0.5;
        guns[37].left.frame_pos[i]=0.5;
        guns[37].right.frame_pos[i]=0.5;
        guns[37].crosshair.frame_pos[i]=0.5;
    }
    for (int i=3; i<6; i++)
    {//setFrame
        guns[37].animation.frame_pos[i]=1.5;
        guns[37].left.frame_pos[i]=0.5;
        guns[37].right.frame_pos[i]=0.5;
        guns[37].crosshair.frame_pos[i]=1.5;
    }



    guns[37].pre.frame_pos[0]=0.1;
    guns[37].left_pre.frame_pos[0]=0.1;
    guns[37].right_pre.frame_pos[0]=0.1;


    guns[37].pre.frame_pos[1]=0.1;
    guns[37].left_pre.frame_pos[1]=0.1;
    guns[37].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<8; i++)
    {
        guns[37].reload.frame_pos[i]=3.1;
        guns[37].left_reload.frame_pos[i]=0.1;
        guns[37].right_reload.frame_pos[i]=3.1;
    }
    for (int i=8; i<16; i++)
    {
        guns[37].reload.frame_pos[i]=3.1;
        guns[37].left_reload.frame_pos[i]=0.1;
        guns[37].right_reload.frame_pos[i]=0.1;
    }
    for (int i=16; i<24; i++)
    {
        guns[37].reload.frame_pos[i]=1.1;
        guns[37].left_reload.frame_pos[i]=0.1;
        guns[37].right_reload.frame_pos[i]=1.1;
    }
    for (int i=24; i<32; i++)
    {
        guns[37].reload.frame_pos[i]=2.1;
        guns[37].left_reload.frame_pos[i]=0.1;
        guns[37].right_reload.frame_pos[i]=2.1;
    }
    for (int i=32; i<40; i++)
    {
        guns[37].reload.frame_pos[i]=1.1;
        guns[37].left_reload.frame_pos[i]=0.1;
        guns[37].right_reload.frame_pos[i]=1.1;
    }
    for (int i=40; i<49; i++)
    {
        guns[37].reload.frame_pos[i]=0.1;
        guns[37].left_reload.frame_pos[i]=0.1;
        guns[37].right_reload.frame_pos[i]=0.1;
    }


    guns[37].buffer.loadFromFile("Sounds/guns/37/0.wav");
    guns[37].sound.setBuffer(guns[37].buffer);

    guns[37].reload_buffer.loadFromFile("Sounds/guns/37/reload0.wav");
    guns[37].reload_sound.setBuffer(guns[37].reload_buffer);

    guns[37].bullet_texture.loadFromFile("Textures/blue_laser.png");
    guns[37].bullet.setTexture(guns[37].bullet_texture);
    guns[37].bullet.setTextureRect(IntRect(0, 0, 1, 2));

    guns[38].name="Rocket Sentry";
    guns[38].cat=2;
    guns[38].x=750;
    guns[38].y=400;
    guns[38].self_damage_multiplier=0.4;
    guns[38].self_explosion_knockback=50;
    guns[38].explosion_knockback=25;
    guns[38].radius=75;
    guns[38].splash_multiplier=1.4;
    guns[38].icon_texture.loadFromFile("Textures/guns/38/icon0.png");
    guns[38].icon.setTexture(guns[38].icon_texture);
    guns[38].damage=70;
    guns[38].proj_speed=75;
    guns[38].spread=0;
    guns[38].create(1, 40, 10, 80);
    guns[38].max_load=12;
    guns[38].max_ammo=12;
    guns[38].isPistol=true;
    guns[38].pre.create(1, 200, 200, 100, 100, 1);
    guns[38].pre.fill_frames("Textures/guns/38/gun", 1);
    guns[38].left_pre.create(1, 100, 100, 50, 50, 1);
    guns[38].left_pre.fill_frames("Textures/guns/38/left", 1);
    guns[38].right_pre.create(1, 100, 100, 50, 50, 1);
    guns[38].right_pre.fill_frames("Textures/guns/38/right", 1);
    guns[38].animation.create(2, 200, 200, 100, 100, 0.1);
    guns[38].animation.fill_frames("Textures/guns/38/gun", 1);
    guns[38].left.create(1, 100, 100, 50, 50, 0.1);
    guns[38].left.fill_frames("Textures/guns/38/left", 1);
    guns[38].right.create(1, 100, 100, 50, 50, 0.1);
    guns[38].right.fill_frames("Textures/guns/38/right", 1);
    guns[38].reload.create(3, 200, 200, 100, 100, 0.1);
    guns[38].reload.fill_frames("Textures/guns/38/reload", 1);
    guns[38].left_reload.create(1, 100, 100, 50, 50, 0.1);
    guns[38].left_reload.fill_frames("Textures/guns/38/left", 1);
    guns[38].right_reload.create(3, 100, 100, 50, 50, 0.1);
    guns[38].right_reload.fill_frames("Textures/guns/38/right_reload", 1);
    guns[38].crosshair.create(2, 200, 200, 100, 100, 0.1);
    guns[38].crosshair.fill_frames("Textures/guns/38/crosshair", 1);
    guns[38].isProjectile=true;
    guns[38].projectile.create(2, 50, 10, 100, 10, 0.1);
    guns[38].projectile.fill_frames("Textures/guns/38/projectile", 1);

    guns[38].blast.create(3, 120, 120, 60, 60, 0.15);
    guns[38].blast.fill_frames("Textures/guns/38/blast", 1);

    guns[38].max_projectile_time=18;
    guns[38].blast.frame_pos=new double[19];
    guns[38].blast.f_count=19;

    for (int i=0; i<6; i++)
    {
        guns[38].blast.frame_pos[i]=2.1;
    }

    for (int i=6; i<12; i++)
    {
        guns[38].blast.frame_pos[i]=1.1;
    }

    for (int i=12; i<19; i++)
    {
        guns[38].blast.frame_pos[i]=0.1;
    }


    guns[38].projectile.frame_pos=new double[17];
    guns[38].projectile.f_count=17;


    for (int i=12; i<17; i++)
    {
        guns[38].projectile.frame_pos[i]=0.1;
    }
    for (int i=6; i<12; i++)
    {
        guns[38].projectile.frame_pos[i]=1.1;
    }
    for (int i=0; i<6; i++)
    {
        guns[38].projectile.frame_pos[i]=0.1;
    }

    //guns[6].


    for (int i=0; i<20; i++)
    {

    guns[38].animation.frame_pos[i]=0.5;
        guns[38].left.frame_pos[i]=0.5;
        guns[38].right.frame_pos[i]=0.5;
        guns[38].crosshair.frame_pos[i]=0.5;
    }

    for (int i=20; i<41; i++)
    {//setFrame
        guns[38].animation.frame_pos[i]=1.5;
        guns[38].left.frame_pos[i]=0.5;
        guns[38].right.frame_pos[i]=0.5;
        guns[38].crosshair.frame_pos[i]=1.5;
    }



    guns[38].pre.frame_pos[0]=0.1;
    guns[38].left_pre.frame_pos[0]=0.1;
    guns[38].right_pre.frame_pos[0]=0.1;


    guns[38].pre.frame_pos[1]=0.1;
    guns[38].left_pre.frame_pos[1]=0.1;
    guns[38].right_pre.frame_pos[1]=0.1;


    for (int i=0; i<16; i++)
    {
        guns[38].reload.frame_pos[i]=0.1;
        guns[38].left_reload.frame_pos[i]=0.1;
        guns[38].right_reload.frame_pos[i]=0.1;
    }
    for (int i=16; i<32; i++)
    {
        guns[38].reload.frame_pos[i]=1.1;
        guns[38].left_reload.frame_pos[i]=0.1;
        guns[38].right_reload.frame_pos[i]=1.1;
    }
    for (int i=32; i<48; i++)
    {
        guns[38].reload.frame_pos[i]=2.1;
        guns[38].left_reload.frame_pos[i]=0.1;
        guns[38].right_reload.frame_pos[i]=2.1;
    }
    for (int i=48; i<64; i++)
    {
        guns[38].reload.frame_pos[i]=1.1;
        guns[38].left_reload.frame_pos[i]=0.1;
        guns[38].right_reload.frame_pos[i]=1.1;
    }
    for (int i=64; i<81; i++)
    {
        guns[38].reload.frame_pos[i]=0.1;
        guns[38].left_reload.frame_pos[i]=0.1;
        guns[38].right_reload.frame_pos[i]=0.1;
    }



    guns[38].buffer.loadFromFile("Sounds/guns/38/0.wav");
    guns[38].sound.setBuffer(guns[38].buffer);

    guns[38].reload_buffer.loadFromFile("Sounds/guns/38/reload0.wav");
    guns[38].reload_sound.setBuffer(guns[38].reload_buffer);

    guns[38].exp_buffer.loadFromFile("Sounds/guns/38/explosion0.wav");


//guns[33




//


    //SoundBuffer step_buffer[14];
    //Sound step[14];

    step[0].buffer.loadFromFile("Sounds/effects/step0.wav");
    step[0].sound.setBuffer(step[0].buffer);
    step[1].buffer.loadFromFile("Sounds/effects/step1.wav");
    step[1].sound.setBuffer(step[1].buffer);
    step[2].buffer.loadFromFile("Sounds/effects/step2.wav");
    step[2].sound.setBuffer(step[2].buffer);
    step[3].buffer.loadFromFile("Sounds/effects/step3.wav");
    step[3].sound.setBuffer(step[3].buffer);
    step[4].buffer.loadFromFile("Sounds/effects/step4.wav");
    step[4].sound.setBuffer(step[4].buffer);
    step[5].buffer.loadFromFile("Sounds/effects/step5.wav");
    step[5].sound.setBuffer(step[5].buffer);
    step[6].buffer.loadFromFile("Sounds/effects/step6.wav");
    step[6].sound.setBuffer(step[6].buffer);
    step[7].buffer.loadFromFile("Sounds/effects/step7.wav");
    step[7].sound.setBuffer(step[7].buffer);
    step[8].buffer.loadFromFile("Sounds/effects/step8.wav");
    step[8].sound.setBuffer(step[8].buffer);
    step[9].buffer.loadFromFile("Sounds/effects/step9.wav");
    step[9].sound.setBuffer(step[9].buffer);
    step[10].buffer.loadFromFile("Sounds/effects/step10.wav");
    step[10].sound.setBuffer(step[10].buffer);
    step[11].buffer.loadFromFile("Sounds/effects/step11.wav");
    step[11].sound.setBuffer(step[11].buffer);
    step[12].buffer.loadFromFile("Sounds/effects/step12.wav");
    step[12].sound.setBuffer(step[12].buffer);
    step[13].buffer.loadFromFile("Sounds/effects/step13.wav");
    step[13].sound.setBuffer(step[13].buffer);
    //std::cout << step[3].sound.getVolume();

    //step[11].setVolume(100);

    //std::cout << step[11].getVolume();

    /*for (int i=0; i<step_count; i++)
    {
        std::string string_temp="";
        string_temp+="Sounds/effects/step";
        string_temp+=std::to_string(i);
        string_temp+=".wav";
        step[i].setS(string_temp);

        std::cout << step[i].sound.getVolume();

        //std::cout << string_temp << "\n\n";
        //step_buffer[i].setBuffer(step_buffer[i]);
        //step[i].openFromFile(string_temp);
        //step[i].setVolume(100);
        //std::cout << step[i].getVolume();
    }*/
    //std::cout << guns[14].reload_sound.getVolume() << "\n\n";
    /*guns[6].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[6].bullet.setTexture(guns[6].bullet_texture);
    guns[6].bullet.setTextureRect(IntRect(0, 0, 1, 2));*/


    /*for (int i=0; i<8; i++)
    {
        guns[0].crosshair_positionx[i]=0;
    }
    for (int i=8; i<13; i++)
    {
        guns[0].crosshair_positionx[i]=200;
    }*/


    /*guns[1].name="Pistol";
    guns[1].max_delay=20;
    guns[1].damage=35;
    guns[1].max_deploy=15;

    for (int i=0; i<12; i++)
    {
        guns[1].crosshair_positionx[i]=0;
    }
    for (int i=12; i<21; i++)
    {
        guns[1].crosshair_positionx[i]=200;
    }

    guns[2].name="Sandgun";
    guns[2].max_delay=2;
    guns[2].damage=4;
    guns[2].max_deploy=30;

    for (int i=0; i<3; i++)
    {
        guns[2].crosshair_positionx[i]=0;
    }

    guns[3].name="Lever Action Rifle";
    guns[3].max_delay=40;
    guns[3].damage=50;

    for (int i=0; i<24; i++)
    {
        guns[3].crosshair_positionx[i]=0;
    }
    for (int i=24; i<41; i++)
    {
        guns[3].crosshair_positionx[i]=200;
    }

    guns[4].name="Laser Rifle";
    guns[4].max_delay=4;
    guns[4].damage=7;
    guns[4].max_deploy=25;

    for (int i=0; i<5; i++)
    {
        guns[4].crosshair_positionx[i]=0;
    }


    guns[5].name="Revolver";
    guns[5].max_delay=60;
    guns[5].damage=65;
    guns[5].max_deploy=10;

    for (int i=0; i<40; i++)
    {
        guns[5].crosshair_positionx[i]=0;
    }
    for (int i=40; i<61; i++)
    {
        guns[5].crosshair_positionx[i]=200;
    }

    guns[6].name="Nailgun";
    guns[6].max_delay=12;
    guns[6].damage=20;
    guns[6].spread=2;
    guns[6].max_deploy=15;

    for (int i=0; i<8; i++)
    {
        guns[6].crosshair_positionx[i]=0;
    }
    for (int i=8; i<13; i++)
    {
        guns[6].crosshair_positionx[i]=200;
    }

    guns[7].name="Submachine Gun";
    guns[7].max_delay=10;
    guns[7].damage=17;
    guns[7].spread=2;

    for (int i=0; i<7; i++)
    {
        guns[7].crosshair_positionx[i]=0;
    }
    for (int i=7; i<11; i++)
    {
        guns[7].crosshair_positionx[i]=200;
    }

    guns[8].name="Laser Gun";
    guns[8].max_delay=150;
    guns[8].damage=120;
    guns[8].max_deploy=35;

    for (int i=0; i<110; i++)
    {
        guns[8].crosshair_positionx[i]=0;
    }
    for (int i=110; i<151; i++)
    {
        guns[8].crosshair_positionx[i]=200;
    }

    guns[9].name="Uzi";
    guns[9].max_delay=5;
    guns[9].damage=8;
    guns[9].spread=3;
    guns[9].max_deploy=15;

    for (int i=0; i<4; i++)
    {
        guns[9].crosshair_positionx[i]=0;
    }
    for (int i=4; i<6; i++)
    {
        guns[9].crosshair_positionx[i]=200;
    }

    guns[10].name="The Old Reliable";
    guns[10].max_delay=240;
    guns[10].damage=40;
    guns[10].max_deploy=15;

    for (int i=0; i<200; i++)
    {
        guns[10].crosshair_positionx[i]=0;
    }
    for (int i=200; i<241; i++)
    {
        guns[10].crosshair_positionx[i]=200;
    }

    guns[11].name="Double Barrel Shotgun";
    guns[11].max_delay=120;
    guns[11].damage=12;

    for (int i=0; i<80; i++)
    {
        guns[11].crosshair_positionx[i]=0;
    }
    for (int i=80; i<121; i++)
    {
        guns[11].crosshair_positionx[i]=200;
    }

    guns[12].name="Auto Shotgun";
    guns[12].max_delay=15;
    guns[12].damage=5;

    for (int i=0; i<10; i++)
    {
        guns[12].crosshair_positionx[i]=0;
    }
    for (int i=10; i<16; i++)
    {
        guns[12].crosshair_positionx[i]=200;
    }

    guns[13].name="Quad Barrel Rocket Launcher";
    guns[13].max_delay=60;
    guns[13].damage=75;
    guns[13].max_deploy=-25;

    for (int i=0; i<35; i++)
    {
        guns[13].crosshair_positionx[i]=0;
    }
    for (int i=35; i<61; i++)
    {
        guns[13].crosshair_positionx[i]=200;
    }

    guns[14].name="Rocket Gatling";
    guns[14].max_delay=12;
    guns[14].damage=27;
    guns[14].max_deploy=25;

    guns[14].proj_width=3;
    guns[14].proj_length=40;

    for (int i=0; i<8; i++)
    {
        guns[14].crosshair_positionx[i]=0;
    }
    for (int i=8; i<13; i++)
    {
        guns[14].crosshair_positionx[i]=200;
    }

    guns[15].name="Hand Gun";
    guns[15].max_delay=40;
    guns[15].damage=55;
    guns[15].splash_multiplier=2;
    guns[15].max_deploy=10;

    guns[15].proj_width=6;
    guns[15].proj_length=6;

    for (int i=0; i<25; i++)
    {
        guns[15].crosshair_positionx[i]=0;
    }
    for (int i=25; i<41; i++)
    {
        guns[15].crosshair_positionx[i]=200;
    }

    guns[16].name="Plasma Rifle";
    guns[16].max_delay=8;
    guns[16].damage=14;
    guns[16].splash_multiplier=2;
    guns[16].spread=2;

    guns[16].proj_width=6;
    guns[16].proj_length=6;

    for (int i=0; i<6; i++)
    {
        guns[16].crosshair_positionx[i]=0;
    }
    for (int i=6; i<9; i++)
    {
        guns[16].crosshair_positionx[i]=200;
    }

    guns[17].name="Flamethrower";
    guns[17].max_delay=2;
    guns[17].damage=6;
    guns[17].max_deploy=30;

    guns[17].proj_width=15;
    guns[17].proj_length=50;

    /*for (int i=0; i<3; i++)
    {
        guns[17].crosshair_positionx[i]=0;
        guns[33].crosshair_positionx[i]=0;
    }*/

    /*guns[18].name="Gauss Gun";
    guns[18].max_delay=60;
    guns[18].damage=75;

    for (int i=0; i<35; i++)
    {
        guns[18].crosshair_positionx[i]=0;
    }
    for (int i=35; i<61; i++)
    {
        guns[18].crosshair_positionx[i]=200;
    }

    guns[19].name="Laser Pistol";
    guns[19].max_delay=165;
    guns[19].damage=120;
    guns[19].max_deploy=25;

    for (int i=0; i<125; i++)
    {
        guns[19].crosshair_positionx[i]=0;
    }
    for (int i=125; i<166; i++)
    {
        guns[19].crosshair_positionx[i]=200;
    }

    guns[20].name="Golden Machine Gun";
    guns[20].max_delay=15;
    guns[20].damage=25;

    for (int i=0; i<10; i++)
    {
        guns[20].crosshair_positionx[i]=0;
    }
    for (int i=10; i<15; i++)
    {
        guns[20].crosshair_positionx[i]=200;
    }

    guns[21].name="Shotgun";
    guns[21].max_delay=45;
    guns[21].damage=10;

    for (int i=0; i<25; i++)
    {
        guns[21].crosshair_positionx[i]=0;
    }
    for (int i=25; i<46; i++)
    {
        guns[21].crosshair_positionx[i]=200;
    }

    guns[22].name="Optic Pistol";
    guns[22].max_delay=2;
    guns[22].damage=3;
    guns[22].max_deploy=10;

    for (int i=0; i<3; i++)
    {
        guns[22].crosshair_positionx[i]=0;
    }

    guns[23].name="Electric Arc";
    guns[23].max_delay=3;
    guns[23].damage=5;

    for (int i=0; i<4; i++)
    {
        guns[23].crosshair_positionx[i]=0;
    }


    guns[24].name="Railgun";
    guns[24].max_delay=180;
    guns[24].damage=150;
    guns[24].max_deploy=35;

    for (int i=0; i<140; i++)
    {
        guns[24].crosshair_positionx[i]=0;
    }
    for (int i=140; i<181; i++)
    {
        guns[24].crosshair_positionx[i]=200;
    }

    guns[25].name="The Zapper";
    guns[25].max_delay=2;
    guns[25].damage=8;
    guns[25].max_deploy=10;

    for (int i=0; i<3; i++)
    {
        guns[25].crosshair_positionx[i]=0;
    }

    guns[26].name="Golden Pistol";
    guns[26].max_delay=30;
    guns[26].damage=45;
    guns[26].max_deploy=15;

    for (int i=0; i<18; i++)
    {
        guns[26].crosshair_positionx[i]=0;
    }
    for (int i=18; i<31; i++)
    {
        guns[26].crosshair_positionx[i]=200;
    }

    guns[27].name="The Mounted Sentry";
    guns[27].max_delay=9;
    guns[27].damage=15;
    guns[27].max_deploy=10;

    for (int i=0; i<7; i++)
    {
        guns[27].crosshair_positionx[i]=0;
    }
    for (int i=7; i<10; i++)
    {
        guns[27].crosshair_positionx[i]=200;
    }

    guns[28].name="Shotgun Uzi";
    guns[28].max_delay=6;
    guns[28].damage=2;
    guns[28].spread=3;
    guns[28].max_deploy=15;

    for (int i=0; i<5; i++)
    {
        guns[28].crosshair_positionx[i]=0;
    }
    for (int i=5; i<7; i++)
    {
        guns[28].crosshair_positionx[i]=200;
    }

    guns[29].name="Boosty & Speedy";
    guns[29].max_delay=3;
    guns[29].damage=4;
    guns[29].max_deploy=10;

    for (int i=0; i<4; i++)
    {
        guns[29].crosshair_positionx[i]=0;
    }

    guns[30].name="Plasma Shotgun";
    guns[30].max_delay=60;
    guns[30].damage=12;
    guns[30].splash_multiplier=2;
    guns[30].proj_width=6;
    guns[30].proj_length=6;
    guns[30].max_deploy=20;

    for (int i=0; i<40; i++)
    {
        guns[30].crosshair_positionx[i]=0;
    }
    for (int i=40; i<61; i++)
    {
        guns[30].crosshair_positionx[i]=200;
    }

    guns[31].name="Rocket Launcher";
    guns[31].max_delay=150;
    guns[31].damage=130;
    guns[31].proj_width=10;
    guns[31].proj_length=100;
    guns[31].max_deploy=-30;

    for (int i=0; i<110; i++)
    {
        guns[31].crosshair_positionx[i]=0;
    }
    for (int i=110; i<151; i++)
    {
        guns[31].crosshair_positionx[i]=200;
    }


    guns[32].isProjectile=true;
    guns[32].radius=75;
    guns[32].proj_speed=9999;
    guns[32].splash_multiplier=1.8;



    guns[32].name="Tesla Rifle";
    guns[32].max_delay=100;
    guns[32].damage=90;
    guns[32].proj_width=1;
    guns[32].proj_length=1;

    for (int i=0; i<60; i++)
    {
        guns[32].crosshair_positionx[i]=0;
    }
    for (int i=60; i<101; i++)
    {
        guns[32].crosshair_positionx[i]=200;
    }


    guns[33].name="Golden Gatling";
    guns[33].max_delay=3;
    guns[33].damage=5;
    guns[33].max_deploy=20;

    guns[33].spread=6;

    guns[33].positionx[0]=0;
    guns[33].positionx[1]=0;
    guns[33].positionx[2]=100;



    guns[34].name="The Knife";
    guns[34].max_delay=30;
    guns[34].damage=100;
    guns[34].max_deploy=5;


    guns[35].name="Skeleton Musket";
    guns[35].max_delay=40;
    guns[35].damage=10;

    for (int i=0; i<20; i++)
    {
        guns[35].crosshair_positionx[i]=0;
        guns[35].positionx[i]=0;
    }
    for (int i=20; i<41; i++)
    {
        guns[35].crosshair_positionx[i]=200;
        guns[35].positionx[i]=100;
    }




    guns[30].isProjectile=true;
    guns[30].radius=25;
    guns[30].proj_speed=100;

    guns[29].positionx[0]=0;
    guns[29].positionx[1]=0;
    guns[29].positionx[2]=0;



    guns[25].proj_width=10;
    guns[25].proj_length=50;

    guns[22].positionx[0]=0;
    guns[22].positionx[1]=100;
    guns[22].positionx[2]=100;

    guns[28].positionx[0]=0;
    guns[28].positionx[1]=0;
    guns[28].positionx[2]=0;
    guns[28].positionx[3]=100;
    guns[28].positionx[4]=100;
    guns[28].positionx[5]=100;


    guns[9].positionx[5]=0;
    guns[9].positionx[4]=100;
    guns[9].positionx[3]=100;
    guns[9].positionx[2]=100;
    guns[9].positionx[1]=0;
    guns[9].positionx[0]=0;

    guns[5].positionx[60]=0;

    guns[7].positionx[6]=0;
    guns[7].positionx[5]=100;
    guns[7].positionx[4]=100;
    guns[7].positionx[3]=100;
    guns[7].positionx[2]=100;
    guns[7].positionx[1]=0;
    guns[7].positionx[0]=0;

    for (int i=0; i<50; i++)
    {
        guns[32].positionx[i]=0;
    }
    for (int i=50; i<101; i++)
    {
        guns[32].positionx[i]=100;
    }

    for (int i=0; i<10; i++)
    {
        guns[20].positionx[i]=0;
    }
    for (int i=10; i<26; i++)
    {
        guns[20].positionx[i]=100;
    }
    for (int i=0; i<50; i++)
    {
        guns[13].positionx[i]=0;
    }
    for (int i=50; i<61; i++)
    {
        guns[13].positionx[i]=100;
    }

    for (int i=5; i<150; i++)
    {
        guns[8].positionx[i]=100;
    }

    for (int i=0; i<45; i++)
    {
        guns[30].positionx[i]=0;
    }
    for (int i=45; i<61; i++)
    {
        guns[30].positionx[i]=100;
    }

    guns[8].positionx[0]=0;
    guns[8].positionx[1]=0;
    guns[8].positionx[2]=0;
    guns[8].positionx[3]=0;
    guns[8].positionx[4]=0;
    guns[8].positionx[150]=0;

    for (int i=0; i<10; i++)
    {
        guns[12].positionx[i]=0;
    }

    for (int i=10; i<16; i++)
    {
        guns[12].positionx[i]=100;
    }

    for (int i=55; i<60; i++)
    {
        guns[5].positionx[i]=100;
        guns[18].positionx[i]=100;
    }

    for (int i=0; i<55; i++)
    {
        guns[5].positionx[i]=0;
        guns[18].positionx[i]=0;
    }

    for (int i=0; i<guns_count; i++)
    {
        for (int j=0; j<240; j++)
        {
            guns[i].right_positionx[j]=0;
            guns[i].left_positionx[j]=0;
        }
    }

    for (int i=0; i<5; i++)
    {
        guns[21].positionx[i]=0;
        guns[21].right_positionx[i]=0;
    }
    for (int i=5; i<15; i++)
    {
        guns[21].positionx[i]=100;
        guns[21].right_positionx[i]=50;
    }
    for (int i=15; i<30; i++)
    {
        guns[21].positionx[i]=200;
        guns[21].right_positionx[i]=100;
    }
    for (int i=30; i<46; i++)
    {
        guns[21].positionx[i]=100;
        guns[21].right_positionx[i]=50;
    }

    for (int i=1; i<210; i++)
    {
        guns[10].positionx[i]=100;
    }
    for (int i=210; i<220; i++)
    {
        guns[10].positionx[i]=0;
    }
    for (int i=220; i<241; i++)
    {
        guns[10].positionx[i]=100;
    }
    for (int i=30; i<60; i++)
    {
        guns[10].right_positionx[i]=100;
    }
    for (int i=60; i<90; i++)
    {
        guns[10].right_positionx[i]=50;
    }
    for (int i=90; i<120; i++)
    {
        guns[10].right_positionx[i]=100;
    }
    for (int i=120; i<150; i++)
    {
        guns[10].right_positionx[i]=50;
    }
    for (int i=150; i<180; i++)
    {//packet
        guns[10].right_positionx[i]=100;
    }
    for (int i=180; i<210; i++)
    {
        guns[10].right_positionx[i]=50;
    }
    guns[10].positionx[0]=0;
    guns[10].right_positionx[0]=0;
    guns[10].left_positionx[0]=0;
    for (int i=0; i<5; i++)
    {
        guns[0].positionx[i]=0;
        guns[1].positionx[i]=0;
        guns[2].positionx[i]=0;
        guns[3].positionx[i]=0;
        guns[4].positionx[i]=0;
        guns[6].positionx[i]=0;
    }

    for (int i=5; i<12; i++)
    {
        guns[0].positionx[i]=100;
        guns[1].positionx[i]=0;
        guns[3].positionx[i]=0;
        guns[6].positionx[i]=100;
    }

    for (int i=12; i<20; i++)
    {
        guns[1].positionx[i]=100;
        guns[3].positionx[i]=200;
    }

    for (int i=20; i<30; i++)
    {
        guns[3].positionx[i]=200;
    }

    for (int i=30; i<40; i++)
    {
        guns[3].positionx[i]=100;
    }

    guns[0].positionx[12]=0;
    guns[1].positionx[35]=0;
    guns[3].positionx[40]=0;

    for (int i=0; i<30; i++)
    {
        guns[31].positionx[i]=0;
        guns[31].left_positionx[i]=0;
        guns[31].right_positionx[i]=0;
    }
    for(int i=30; i<60; i++)
    {
        guns[31].positionx[i]=300;
        guns[31].right_positionx[i]=100;
        guns[31].left_positionx[i]=50;
    }
    for(int i=60; i<90; i++)
    {
        guns[31].positionx[i]=200;
        guns[31].right_positionx[i]=50;
        guns[31].left_positionx[i]=50;
    }
    for(int i=90; i<120; i++)
    {
        guns[31].positionx[i]=0;
        guns[31].right_positionx[i]=0;
        guns[31].left_positionx[i]=0;
    }
    for(int i=120; i<150; i++)
    {
        guns[31].positionx[i]=100;
        guns[31].right_positionx[i]=0;
        guns[31].left_positionx[i]=0;
    }

    for (int i=0; i<10; i++)
    {

        player.body_sprite_positionx[i]=0;
        for (int j=0; j<types; j++)
            for (int k=0; k<enemy_count; k++)
                enemy[j][k].body_sprite_positionx[i]=0;
    }

    for (int i=10; i<20; i++)
    {
        player.body_sprite_positionx[i]=100;
        for (int j=0; j<types; j++)
            for (int k=0; k<enemy_count; k++)
                enemy[j][k].body_sprite_positionx[i]=100;
    }

    for (int i=20; i<30; i++)
    {
        player.body_sprite_positionx[i]=200;
        for (int j=0; j<types; j++)
            for (int k=0; k<enemy_count; k++)
                enemy[j][k].body_sprite_positionx[i]=200;
    }

    for (int i=0; i<30; i++)
    {
        guns[11].positionx[i]=0;
    }
    for (int i=30; i<60; i++)
    {
        guns[11].positionx[i]=200;
        guns[11].right_positionx[i]=50;
    }
    for (int i=60; i<90; i++)
    {
        guns[11].positionx[i]=200;
        guns[11].right_positionx[i]=100;
    }
    for (int i=90; i<100; i++)
    {
        guns[11].positionx[i]=0;
    }
    for (int i=100; i<121; i++)
    {
        guns[11].positionx[i]=100;
    }

    for (int i=0; i<7; i++)
    {
        guns[14].positionx[i]=0;
    }
    for (int i=7; i<13; i++)
    {
        guns[14].positionx[i]=100;
    }

    for (int i=0; i<41; i++)
    {
        guns[15].positionx[i]=0;
    }
    for (int i=0; i<5; i++)
    {
        guns[16].positionx[i]=0;
    }
    for (int i=5; i<9; i++)
    {
        guns[16].positionx[i]=100;
    }


    for (int i=1; i<150; i++)
    {
        guns[24].positionx[i]=200;
    }
    for (int i=150; i<181; i++)
    {
        guns[24].positionx[i]=100;
        guns[24].right_positionx[i]=50;
        guns[24].left_positionx[i]=50;
    }

    for (int i=0; i<5; i++)
    {
        guns[26].positionx[i]=0;
    }
    for (int i=5; i<31; i++)
    {
        guns[26].positionx[i]=100;
    }

    for (int i=0; i<5; i++)
    {
        guns[27].positionx[i]=0;
    }
    for (int i=5; i<10; i++)
    {
        guns[27].positionx[i]=100;
    }

    for (int i=0; i<16; i++)
    {
        guns[34].positionx[i]=0;
        guns[34].left_positionx[i]=0;
        guns[34].crosshair_positionx[i]=0;
    }
    for (int i=16; i<31; i++)
    {
        guns[34].positionx[i]=100;
        guns[34].left_positionx[i]=50;
        guns[34].crosshair_positionx[i]=0;
    }


    //window.setMouseCursorVisible(false);

    //setmapborders();


    guns[0].buffer.loadFromFile("Sounds/guns/machine_gun/machine_gun_sound.wav");
    guns[0].sound.setBuffer(guns[0].buffer);
    guns[1].buffer.loadFromFile("Sounds/guns/pistol/pistol_sound.wav");
    guns[1].sound.setBuffer(guns[1].buffer);
    guns[2].buffer.loadFromFile("Sounds/guns/sandgun/sandgun_sound.wav");
    guns[2].sound.setBuffer(guns[2].buffer);
    guns[3].buffer.loadFromFile("Sounds/guns/lever_action/lever_sound.wav");
    guns[3].sound.setBuffer(guns[3].buffer);
    guns[4].buffer.loadFromFile("Sounds/guns/laser_rifle/laser_sound.wav");
    guns[4].sound.setBuffer(guns[4].buffer);
    guns[5].buffer.loadFromFile("Sounds/guns/revolver/revolver_sound.wav");
    guns[5].sound.setBuffer(guns[5].buffer);
    guns[6].buffer.loadFromFile("Sounds/guns/nailgun/nailgun_sound.wav");
    guns[6].sound.setBuffer(guns[6].buffer);
    guns[7].buffer.loadFromFile("Sounds/guns/smg/smg_sound.wav");
    guns[7].sound.setBuffer(guns[7].buffer);
    guns[8].buffer.loadFromFile("Sounds/guns/lasergun/lasergun_sound.wav");
    guns[8].sound.setBuffer(guns[8].buffer);
    guns[9].buffer.loadFromFile("Sounds/guns/uzi/uzi_sound.wav");
    guns[9].sound.setBuffer(guns[9].buffer);
    guns[10].buffer.loadFromFile("Sounds/guns/flintlock/sound.wav");
    guns[10].sound.setBuffer(guns[10].buffer);
    guns[11].buffer.loadFromFile("Sounds/guns/double/sound.wav");
    guns[11].sound.setBuffer(guns[11].buffer);
    guns[12].buffer.loadFromFile("Sounds/guns/auto_shotgun/sound.wav");
    guns[12].sound.setBuffer(guns[12].buffer);
    guns[13].exp_buffer.loadFromFile("Sounds/guns/4barrel/explosion.wav");
    guns[13].buffer.loadFromFile("Sounds/guns/4barrel/sound.wav");
    guns[13].sound.setBuffer(guns[13].buffer);
    guns[14].exp_buffer.loadFromFile("Sounds/guns/4barrel/explosion.wav");
    guns[14].buffer.loadFromFile("Sounds/guns/rocket_minigun/sound.wav");
    guns[14].sound.setBuffer(guns[14].buffer);
    guns[15].exp_buffer.loadFromFile("Sounds/guns/handgun/explosion.wav");
    guns[15].buffer.loadFromFile("Sounds/guns/handgun/sound.wav");
    guns[15].sound.setBuffer(guns[15].buffer);
    guns[16].exp_buffer.loadFromFile("Sounds/guns/handgun/explosion.wav");
    guns[16].buffer.loadFromFile("Sounds/guns/handgun/sound.wav");
    guns[16].sound.setBuffer(guns[16].buffer);
    //guns[17].exp_buffer.loadFromFile("Sounds/guns/flamethrower/sound.wav");
    guns[17].buffer.loadFromFile("Sounds/guns/flamethrower/sound.wav");
    guns[17].sound.setBuffer(guns[17].buffer);
    guns[18].buffer.loadFromFile("Sounds/guns/gauss/sound.wav");
    guns[18].sound.setBuffer(guns[18].buffer);
    guns[19].buffer.loadFromFile("Sounds/guns/laserpistol/sound.wav");
    guns[19].sound.setBuffer(guns[19].buffer);
    guns[20].buffer.loadFromFile("Sounds/guns/goldenmg/sound.wav");
    guns[20].sound.setBuffer(guns[20].buffer);
    guns[21].buffer.loadFromFile("Sounds/guns/shotgun/sound.wav");
    guns[21].sound.setBuffer(guns[21].buffer);
    guns[22].buffer.loadFromFile("Sounds/guns/optic/sound.wav");
    guns[22].sound.setBuffer(guns[22].buffer);
    guns[23].buffer.loadFromFile("Sounds/guns/electric_arc/sound.wav");
    guns[23].sound.setBuffer(guns[23].buffer);
    guns[24].buffer.loadFromFile("Sounds/guns/railgun/sound.wav");
    guns[24].sound.setBuffer(guns[24].buffer);
    guns[25].buffer.loadFromFile("Sounds/guns/zapper/sound.wav");
    guns[25].sound.setBuffer(guns[25].buffer);
    guns[26].buffer.loadFromFile("Sounds/guns/goldenpistol/sound.wav");
    guns[26].sound.setBuffer(guns[26].buffer);
    guns[27].buffer.loadFromFile("Sounds/guns/mounted_sentry/sound.wav");
    guns[27].sound.setBuffer(guns[27].buffer);
    guns[28].buffer.loadFromFile("Sounds/guns/shotgun_uzi/sound.wav");
    guns[28].sound.setBuffer(guns[28].buffer);
    guns[29].buffer.loadFromFile("Sounds/guns/boosty&speedy/sound.wav");
    guns[29].sound.setBuffer(guns[29].buffer);
    guns[30].exp_buffer.loadFromFile("Sounds/guns/handgun/explosion.wav");
    guns[30].buffer.loadFromFile("Sounds/guns/plasma_shotgun/sound.wav");
    guns[30].sound.setBuffer(guns[30].buffer);
    guns[31].exp_buffer.loadFromFile("Sounds/guns/rocket_launcher/explosion.wav");
    guns[31].buffer.loadFromFile("Sounds/guns/4barrel/sound.wav");
    guns[31].sound.setBuffer(guns[31].buffer);
    guns[32].buffer.loadFromFile("Sounds/guns/tesla_rifle/sound.wav");
    guns[32].sound.setBuffer(guns[32].buffer);
    guns[33].buffer.loadFromFile("Sounds/guns/gatling/sound.wav");
    guns[33].sound.setBuffer(guns[33].buffer);
    guns[34].buffer.loadFromFile("Sounds/guns/knife/sound.wav");
    guns[34].sound.setBuffer(guns[34].buffer);
    guns[35].buffer.loadFromFile("Sounds/guns/skeleton/sound.wav");
    guns[35].sound.setBuffer(guns[35].buffer);*/

    Text health_text("", font, 50);
    health_text.setColor(Color::Red);
    health_text.setStyle(Text::Bold);
    health_text.setPosition(1180, 1000);

    //SoundBuffer step_buffer[14];






    /*SoundBuffer hit_buffer;
    hit_buffer.loadFromFile("Sounds/effects/hit.wav");
    Sound hitsound;
    hitsound.setBuffer(hit_buffer);


    SoundBuffer kill_buffer;
    kill_buffer.loadFromFile("Sounds/effects/kill/.wav");
    Sound killsound;
    killsound.setBuffer(kill_buffer);*/


    Text victory("Victory", font, 200);
    victory.setColor(Color::Red);
    victory.setStyle(Text::Bold);
    victory.setPosition(100, 300);

    Text wave_text("", font, 200);
    wave_text.setColor(Color::Red);
    wave_text.setStyle(Text::Bold);
    wave_text.setPosition(100, 300);
    String wave_string="";

    Text kills("", font, 50);
    kills.setColor(Color::Red);
    kills.setStyle(Text::Bold);
    kills.setPosition(50, 50);
    Text deaths("", font, 50);
    deaths.setColor(Color::Red);
    deaths.setStyle(Text::Bold);
    deaths.setPosition(50, 100);
    String points_string="";
    String enemy_points_string="";
    int points=0;
    int enemy_points=0;

    Image image;
    Texture menu_texture;
    menu_texture.loadFromFile("Textures/Menu.png");

    Texture frame_texture;
    frame_texture.loadFromFile("Textures/frame.png");

    Sprite frame;
    frame.setTexture(frame_texture);

    Texture enemy_health_texture;
    enemy_health_texture.loadFromFile("Textures/healthbar.png");
    Texture health_texture;
    health_texture.loadFromFile("Textures/hp_bar.png");
    Text passive_text[2];
    int passive_x[2];
    int passive_y[2];

    passive_x[0]=300;
    passive_x[1]=450;

    passive_y[0]=100;
    passive_y[1]=100;
    passive_text[0].setString("Armor\nHealth +24");
    passive_text[1].setString("Speed Boots\nSpeed +50%");

    passive_text[0].setFont(font);
    passive_text[1].setFont(font);

    passive_text[0].setPosition(1620, 600);
    passive_text[1].setPosition(1620, 600);

    passive_text[0].setColor(Color(0, 127, 0));
    passive_text[1].setColor(Color(0, 127, 0));

    passive_text[0].setCharacterSize(25);
    passive_text[1].setCharacterSize(25);


    passive_text[0].setStyle(Text::Regular);
    passive_text[1].setStyle(Text::Regular);



    Texture passive_texture[2];
    Texture texture;
    Texture crosshair_texture;
    passive_texture[0].loadFromFile("Textures/passive/armor_button.png");
    passive_texture[1].loadFromFile("Textures/passive/speed_boots_button.png");
    Texture map_texture;
    Texture comic_texture;
    Texture hitmarkers;
    Texture killmarkers;
    hitmarkers.loadFromFile("Textures/hit.png");
    killmarkers.loadFromFile("Textures/kill.png");

    Sprite markers;


    Button connect_button;
    connect_button.create("Textures/connect_button.png", "Textures/connect_button2.png", 1180, 650, 300, 50);


    Button multiplayer_button;
    multiplayer_button.create("Textures/multiplayer_button.png", "Textures/multiplayer_button2.png", 1180, 440, 300, 200);

    Button shooting_range_button;
    shooting_range_button.create("Textures/shooting_range_button.png", "Textures/shooting_range_button2.png", 440, 440, 300, 200);

    Button armory_button;
    armory_button.create("Textures/armory_button.png", "Textures/armory_button2.png", 100, 780, 300, 200);

    Button start;
    start.create("Textures/start_button.png", "Textures/start_button2.png", 810, 440, 300, 200);

    Button quit;
    quit.create("Textures/quit_button.png", "Textures/quit_button2.png", 1520, 780, 300, 200);

    Button arena_button;
    arena_button.create("Textures/arena_button.png", "Textures/arena_button2.png", 810, 780, 300, 200);

    Button* comic_button=new Button[comic_count];
    comic_button[0].create("Textures/levels/comic_button.png", "Textures/levels/comic_button_blue.png", 200, 200, 80, 80);
    comic_button[1].create("Textures/levels/comic_button.png", "Textures/levels/comic_button_blue.png", 1000, 200, 80, 80);

    Button* level_button=new Button[levels_count];
    level_button[0].create("Textures/levels/level1.png", "Textures/levels/level1_blue.png", 400, 200, 80, 80);
    level_button[1].create("Textures/levels/level2.png", "Textures/levels/level2_blue.png", 600, 200, 80, 80);
    level_button[2].create("Textures/levels/level3.png", "Textures/levels/level3_blue.png", 800, 200, 80, 80);
    level_button[3].create("Textures/levels/level4.png", "Textures/levels/level4_blue.png", 200, 400, 80, 80);
    level_button[4].create("Textures/levels/level5.png", "Textures/levels/level5_blue.png", 400, 400, 80, 80);
    level_button[5].create("Textures/levels/level6.png", "Textures/levels/level6_blue.png", 600, 400, 80, 80);
    level_button[6].create("Textures/levels/level7.png", "Textures/levels/level7_blue.png", 800, 400, 80, 80);

    //Sprite connect_button;
    //connect_button.setPosition(1180, 650);
    //Sprite multiplayer_button;
    //multiplayer_button.setPosition(1180, 440);
    //Sprite shooting_range_button;
    //shooting_range_button.setPosition(440, 440);
    //Sprite armory_button;
    //armory_button.setPosition(100, 780);
    //Sprite start;
    //start.setPosition(810, 440);
    //Sprite quit;
    //quit.setPosition(1520, 780);




    Sprite comic;
    Sprite enemy_health;
    enemy_health.setTexture(enemy_health_texture);
    Sprite health;
    health.setTexture(health_texture);
    Sprite sprite;
    sprite.setScale(4, 4);
    health.setPosition(760, 1000);
    Sprite crosshair;
    Button arrow_button[8];
    arrow_button[0].create("Textures/red_arrow_up.png", "Textures/blue_arrow_up.png", 810, 195, 100, 45);
    arrow_button[1].create("Textures/red_arrow.png", "Textures/blue_arrow.png", 810, 340, 100, 45);

    arrow_button[2].create("Textures/red_arrow.png", "Textures/blue_arrow.png", 910, 740, 100, 45);
    arrow_button[3].create("Textures/red_arrow.png", "Textures/blue_arrow.png", 710, 740, 100, 45);
    arrow_button[4].create("Textures/red_arrow.png", "Textures/blue_arrow.png", 1110, 740, 100, 45);

    arrow_button[5].create("Textures/red_arrow_up.png", "Textures/blue_arrow_up.png", 910, 595, 100, 45);
    arrow_button[6].create("Textures/red_arrow_up.png", "Textures/blue_arrow_up.png", 710, 595, 100, 45);
    arrow_button[7].create("Textures/red_arrow_up.png", "Textures/blue_arrow_up.png", 1110, 595, 100, 45);
    Sprite icon;


    Sprite passive_icon;
    passive_icon.setTexture(passive_texture[0]);
    passive_icon.setPosition(810, 240);

    Sprite map_sprite;



    Sprite menu;
    menu.setTexture(menu_texture);
    menu.setPosition(0, 0);
    //Sprite arena_button;game_state=main_menu
    //arena_button.setPosition(810, 780);
    //Sprite map_button1;
    //map_button1.setTexture(map_texture1);
    //map_button1.setPosition (200, 200);
    //map_button1.setScale(0.125, 0.125);
    //Sprite map_button2;
    //map_button2.setTexture(map_texture2);
    //map_button2.setPosition (600, 200);
    //map_button2.setScale(0.125, 0.125);


    image.loadFromFile("Textures/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    crosshair_texture.loadFromImage(image);
    crosshair.setTexture(crosshair_texture);

    map_sprite.scale(4, 4);


    player.body.create(6, 100, 100, 50, 0, 1);
    player.body.fill_frames("Textures/player/", 1);
    player.body.setPR(1, 960, 540, 0);
    player.head.create(2, 50, 50, 25, 50, 0.05);
    player.head.setPR(1, 960, 540, 0);
    player.head.fill_frames("Textures/player/head", 1);
    player.idle.loadFromFile("Textures/player/idle.png");
    player.jump.loadFromFile("Textures/player/jump.png");


    /*image.loadFromFile("Textures/player/body1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.body_texture1.loadFromImage(image);
    player.body1.setTexture(player.body_texture1);
    image.loadFromFile("Textures/player/body4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.body_texture4.loadFromImage(image);
    player.body4.setTexture(player.body_texture4);

    image.loadFromFile("Textures/player/head2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.head_texture2.loadFromImage(image);
    player.head2.setTexture(player.head_texture2);
    image.loadFromFile("Textures/player/head3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.head_texture3.loadFromImage(image);
    player.head3.setTexture(player.head_texture3);*/

    /*image.loadFromFile("Textures/guns/machine_gun/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[0].crosshair_texture.loadFromImage(image);
    guns[0].crosshair.setTexture(guns[0].crosshair_texture);
    guns[0].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[0].bullet.setTexture(guns[0].bullet_texture);
    image.loadFromFile("Textures/guns/machine_gun/machine_gun1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[0].texture1.loadFromImage(image);
    guns[0].sprite1.setTexture(guns[0].texture1);
    image.loadFromFile("Textures/guns/machine_gun/machine_gun2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[0].texture2.loadFromImage(image);
    guns[0].sprite2.setTexture(guns[0].texture2);
    image.loadFromFile("Textures/guns/machine_gun/machine_gun3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[0].texture3.loadFromImage(image);
    guns[0].sprite3.setTexture(guns[0].texture3);
    image.loadFromFile("Textures/guns/machine_gun/machine_gun4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[0].texture4.loadFromImage(image);
    guns[0].sprite4.setTexture(guns[0].texture4);
    guns[0].icon_texture.loadFromFile("Textures/guns/machine_gun/machine_gun_button.png");
    guns[0].icon.setTexture(guns[0].icon_texture);*/


    /*image.loadFromFile("Textures/guns/pistol/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[1].crosshair_texture.loadFromImage(image);
    guns[1].crosshair.setTexture(guns[1].crosshair_texture);
    guns[1].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[1].bullet.setTexture(guns[1].bullet_texture);
    image.loadFromFile("Textures/guns/pistol/pistol1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[1].texture1.loadFromImage(image);
    guns[1].sprite1.setTexture(guns[1].texture1);
    image.loadFromFile("Textures/guns/pistol/pistol2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[1].texture2.loadFromImage(image);
    guns[1].sprite2.setTexture(guns[1].texture2);
    image.loadFromFile("Textures/guns/pistol/pistol3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[1].texture3.loadFromImage(image);
    guns[1].sprite3.setTexture(guns[1].texture3);
    image.loadFromFile("Textures/guns/pistol/pistol4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[1].texture4.loadFromImage(image);
    guns[1].sprite4.setTexture(guns[1].texture4);
    guns[1].icon_texture.loadFromFile("Textures/guns/pistol/pistol_button.png");
    guns[1].icon.setTexture(guns[1].icon_texture);


    image.loadFromFile("Textures/guns/sandgun/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[2].crosshair_texture.loadFromImage(image);
    guns[2].crosshair.setTexture(guns[2].crosshair_texture);
    guns[2].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[2].bullet.setTexture(guns[2].bullet_texture);
    image.loadFromFile("Textures/guns/sandgun/sandgun1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[2].texture1.loadFromImage(image);
    guns[2].sprite1.setTexture(guns[2].texture1);
    image.loadFromFile("Textures/guns/sandgun/sandgun2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[2].texture2.loadFromImage(image);
    guns[2].sprite2.setTexture(guns[2].texture2);
    image.loadFromFile("Textures/guns/sandgun/sandgun3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[2].texture3.loadFromImage(image);
    guns[2].sprite3.setTexture(guns[2].texture3);
    image.loadFromFile("Textures/guns/sandgun/sandgun4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[2].texture4.loadFromImage(image);
    guns[2].sprite4.setTexture(guns[2].texture4);
    guns[2].icon_texture.loadFromFile("Textures/guns/sandgun/sandgun_button.png");
    guns[2].icon.setTexture(guns[2].icon_texture);


    image.loadFromFile("Textures/guns/lever_action/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[3].crosshair_texture.loadFromImage(image);
    guns[3].crosshair.setTexture(guns[3].crosshair_texture);
    guns[3].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[3].bullet.setTexture(guns[3].bullet_texture);
    image.loadFromFile("Textures/guns/lever_action/lever_action1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[3].texture1.loadFromImage(image);
    guns[3].sprite1.setTexture(guns[3].texture1);
    image.loadFromFile("Textures/guns/lever_action/lever_action2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[3].texture2.loadFromImage(image);
    guns[3].sprite2.setTexture(guns[3].texture2);
    image.loadFromFile("Textures/guns/lever_action/lever_action3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[3].texture3.loadFromImage(image);
    guns[3].sprite3.setTexture(guns[3].texture3);
    image.loadFromFile("Textures/guns/lever_action/lever_action4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[3].texture4.loadFromImage(image);
    guns[3].sprite4.setTexture(guns[3].texture4);
    guns[3].icon_texture.loadFromFile("Textures/guns/lever_action/lever_action_button.png");
    guns[3].icon.setTexture(guns[3].icon_texture);


    image.loadFromFile("Textures/guns/laser_rifle/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[4].crosshair_texture.loadFromImage(image);
    guns[4].crosshair.setTexture(guns[4].crosshair_texture);
    guns[4].bullet_texture.loadFromFile("Textures/red_laser.png");
    guns[4].bullet.setTexture(guns[4].bullet_texture);
    image.loadFromFile("Textures/guns/laser_rifle/laser1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[4].texture1.loadFromImage(image);
    guns[4].sprite1.setTexture(guns[4].texture1);
    image.loadFromFile("Textures/guns/laser_rifle/laser2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[4].texture2.loadFromImage(image);
    guns[4].sprite2.setTexture(guns[4].texture2);
    image.loadFromFile("Textures/guns/laser_rifle/laser3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[4].texture3.loadFromImage(image);
    guns[4].sprite3.setTexture(guns[4].texture3);
    image.loadFromFile("Textures/guns/laser_rifle/laser4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[4].texture4.loadFromImage(image);
    guns[4].sprite4.setTexture(guns[4].texture4);
    guns[4].icon_texture.loadFromFile("Textures/guns/laser_rifle/laser_button.png");
    guns[4].icon.setTexture(guns[4].icon_texture);


    image.loadFromFile("Textures/guns/revolver/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[5].crosshair_texture.loadFromImage(image);
    guns[5].crosshair.setTexture(guns[5].crosshair_texture);
    guns[5].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[5].bullet.setTexture(guns[5].bullet_texture);
    image.loadFromFile("Textures/guns/revolver/revolver1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[5].texture1.loadFromImage(image);
    guns[5].sprite1.setTexture(guns[5].texture1);
    image.loadFromFile("Textures/guns/revolver/revolver2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[5].texture2.loadFromImage(image);
    guns[5].sprite2.setTexture(guns[5].texture2);
    image.loadFromFile("Textures/guns/revolver/revolver3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[5].texture3.loadFromImage(image);
    guns[5].sprite3.setTexture(guns[5].texture3);
    image.loadFromFile("Textures/guns/revolver/revolver4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[5].texture4.loadFromImage(image);
    guns[5].sprite4.setTexture(guns[5].texture4);
    guns[5].icon_texture.loadFromFile("Textures/guns/revolver/revolver_button.png");
    guns[5].icon.setTexture(guns[5].icon_texture);


    image.loadFromFile("Textures/guns/nailgun/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[6].crosshair_texture.loadFromImage(image);
    guns[6].crosshair.setTexture(guns[6].crosshair_texture);
    guns[6].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[6].bullet.setTexture(guns[6].bullet_texture);
    image.loadFromFile("Textures/guns/nailgun/nailgun1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[6].texture1.loadFromImage(image);
    guns[6].sprite1.setTexture(guns[6].texture1);
    image.loadFromFile("Textures/guns/nailgun/nailgun2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[6].texture2.loadFromImage(image);
    guns[6].sprite2.setTexture(guns[6].texture2);
    image.loadFromFile("Textures/guns/nailgun/nailgun3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[6].texture3.loadFromImage(image);
    guns[6].sprite3.setTexture(guns[6].texture3);
    image.loadFromFile("Textures/guns/nailgun/nailgun4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[6].texture4.loadFromImage(image);
    guns[6].sprite4.setTexture(guns[6].texture4);
    guns[6].icon_texture.loadFromFile("Textures/guns/nailgun/nailgun_button.png");
    guns[6].icon.setTexture(guns[6].icon_texture);


    image.loadFromFile("Textures/guns/smg/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[7].crosshair_texture.loadFromImage(image);
    guns[7].crosshair.setTexture(guns[7].crosshair_texture);
    guns[7].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[7].bullet.setTexture(guns[7].bullet_texture);
    image.loadFromFile("Textures/guns/smg/smg1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[7].texture1.loadFromImage(image);
    guns[7].sprite1.setTexture(guns[7].texture1);
    image.loadFromFile("Textures/guns/smg/smg2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[7].texture2.loadFromImage(image);
    guns[7].sprite2.setTexture(guns[7].texture2);
    image.loadFromFile("Textures/guns/smg/smg3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[7].texture3.loadFromImage(image);
    guns[7].sprite3.setTexture(guns[7].texture3);
    image.loadFromFile("Textures/guns/smg/smg4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[7].texture4.loadFromImage(image);
    guns[7].sprite4.setTexture(guns[7].texture4);
    guns[7].icon_texture.loadFromFile("Textures/guns/smg/smg_button.png");
    guns[7].icon.setTexture(guns[7].icon_texture);


    image.loadFromFile("Textures/guns/lasergun/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[8].crosshair_texture.loadFromImage(image);
    guns[8].crosshair.setTexture(guns[8].crosshair_texture);
    guns[8].bullet_texture.loadFromFile("Textures/purple_laser.png");
    guns[8].bullet.setTexture(guns[8].bullet_texture);
    image.loadFromFile("Textures/guns/lasergun/lasergun1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[8].texture1.loadFromImage(image);
    guns[8].sprite1.setTexture(guns[8].texture1);
    image.loadFromFile("Textures/guns/lasergun/lasergun2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[8].texture2.loadFromImage(image);
    guns[8].sprite2.setTexture(guns[8].texture2);
    image.loadFromFile("Textures/guns/lasergun/lasergun3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[8].texture3.loadFromImage(image);
    guns[8].sprite3.setTexture(guns[8].texture3);
    image.loadFromFile("Textures/guns/lasergun/lasergun4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[8].texture4.loadFromImage(image);
    guns[8].sprite4.setTexture(guns[8].texture4);
    guns[8].icon_texture.loadFromFile("Textures/guns/lasergun/lasergun_button.png");
    guns[8].icon.setTexture(guns[8].icon_texture);


    image.loadFromFile("Textures/guns/uzi/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[9].crosshair_texture.loadFromImage(image);
    guns[9].crosshair.setTexture(guns[9].crosshair_texture);
    guns[9].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[9].bullet.setTexture(guns[9].bullet_texture);
    image.loadFromFile("Textures/guns/uzi/uzi1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[9].texture1.loadFromImage(image);
    guns[9].sprite1.setTexture(guns[9].texture1);
    image.loadFromFile("Textures/guns/uzi/uzi2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[9].texture2.loadFromImage(image);
    guns[9].sprite2.setTexture(guns[9].texture2);
    image.loadFromFile("Textures/guns/uzi/uzi3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[9].texture3.loadFromImage(image);
    guns[9].sprite3.setTexture(guns[9].texture3);
    image.loadFromFile("Textures/guns/uzi/uzi4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[9].texture4.loadFromImage(image);
    guns[9].sprite4.setTexture(guns[9].texture4);
    guns[9].icon_texture.loadFromFile("Textures/guns/uzi/uzi_button.png");
    guns[9].icon.setTexture(guns[9].icon_texture);


    image.loadFromFile("Textures/guns/flintlock/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[10].crosshair_texture.loadFromImage(image);
    guns[10].crosshair.setTexture(guns[10].crosshair_texture);
    guns[10].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[10].bullet.setTexture(guns[10].bullet_texture);
    image.loadFromFile("Textures/guns/flintlock/flintlock1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[10].texture1.loadFromImage(image);
    guns[10].sprite1.setTexture(guns[10].texture1);
    image.loadFromFile("Textures/guns/flintlock/flintlock2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[10].texture2.loadFromImage(image);
    guns[10].sprite2.setTexture(guns[10].texture2);
    image.loadFromFile("Textures/guns/flintlock/flintlock3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[10].texture3.loadFromImage(image);
    guns[10].sprite3.setTexture(guns[10].texture3);
    image.loadFromFile("Textures/guns/flintlock/flintlock4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[10].texture4.loadFromImage(image);
    guns[10].sprite4.setTexture(guns[10].texture4);
    guns[10].icon_texture.loadFromFile("Textures/guns/flintlock/icon.png");
    guns[10].icon.setTexture(guns[10].icon_texture);


    image.loadFromFile("Textures/guns/double/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[11].crosshair_texture.loadFromImage(image);
    guns[11].crosshair.setTexture(guns[11].crosshair_texture);
    guns[11].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[11].bullet.setTexture(guns[11].bullet_texture);
    image.loadFromFile("Textures/guns/double/double1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[11].texture1.loadFromImage(image);
    guns[11].sprite1.setTexture(guns[11].texture1);
    image.loadFromFile("Textures/guns/double/double2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[11].texture2.loadFromImage(image);
    guns[11].sprite2.setTexture(guns[11].texture2);
    image.loadFromFile("Textures/guns/double/double3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[11].texture3.loadFromImage(image);
    guns[11].sprite3.setTexture(guns[11].texture3);
    image.loadFromFile("Textures/guns/double/double4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[11].texture4.loadFromImage(image);
    guns[11].sprite4.setTexture(guns[11].texture4);
    guns[11].icon_texture.loadFromFile("Textures/guns/double/icon.png");
    guns[11].icon.setTexture(guns[11].icon_texture);


    image.loadFromFile("Textures/guns/auto_shotgun/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[12].crosshair_texture.loadFromImage(image);
    guns[12].crosshair.setTexture(guns[12].crosshair_texture);
    guns[12].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[12].bullet.setTexture(guns[12].bullet_texture);
    image.loadFromFile("Textures/guns/auto_shotgun/auto1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[12].texture1.loadFromImage(image);
    guns[12].sprite1.setTexture(guns[12].texture1);
    image.loadFromFile("Textures/guns/auto_shotgun/auto2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[12].texture2.loadFromImage(image);
    guns[12].sprite2.setTexture(guns[12].texture2);
    image.loadFromFile("Textures/guns/auto_shotgun/auto3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[12].texture3.loadFromImage(image);
    guns[12].sprite3.setTexture(guns[12].texture3);
    image.loadFromFile("Textures/guns/auto_shotgun/auto4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[12].texture4.loadFromImage(image);
    guns[12].sprite4.setTexture(guns[12].texture4);
    guns[12].icon_texture.loadFromFile("Textures/guns/auto_shotgun/icon.png");
    guns[12].icon.setTexture(guns[12].icon_texture);


    image.loadFromFile("Textures/guns/4barrel/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[13].crosshair_texture.loadFromImage(image);
    guns[13].crosshair.setTexture(guns[13].crosshair_texture);
    image.loadFromFile("Textures/guns/4barrel/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[13].texture1.loadFromImage(image);
    guns[13].sprite1.setTexture(guns[13].texture1);
    image.loadFromFile("Textures/guns/4barrel/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[13].texture2.loadFromImage(image);
    guns[13].sprite2.setTexture(guns[13].texture2);
    image.loadFromFile("Textures/guns/4barrel/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[13].texture3.loadFromImage(image);
    guns[13].sprite3.setTexture(guns[13].texture3);
    image.loadFromFile("Textures/guns/4barrel/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[13].texture4.loadFromImage(image);
    guns[13].sprite4.setTexture(guns[13].texture4);
    guns[13].icon_texture.loadFromFile("Textures/guns/4barrel/icon.png");
    guns[13].icon.setTexture(guns[13].icon_texture);
    image.loadFromFile("Textures/guns/4barrel/proj1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[13].proj_texture1.loadFromImage(image);
    image.loadFromFile("Textures/guns/4barrel/proj2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[13].proj_texture2.loadFromImage(image);
    image.loadFromFile("Textures/guns/4barrel/proj3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[13].proj_texture3.loadFromImage(image);
    image.loadFromFile("Textures/guns/4barrel/proj4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[13].proj_texture4.loadFromImage(image);
    image.loadFromFile("Textures/guns/4barrel/blast.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[13].blast.loadFromImage(image);


    image.loadFromFile("Textures/guns/rocket_minigun/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[14].crosshair_texture.loadFromImage(image);
    guns[14].crosshair.setTexture(guns[14].crosshair_texture);
    image.loadFromFile("Textures/guns/rocket_minigun/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[14].texture1.loadFromImage(image);
    guns[14].sprite1.setTexture(guns[14].texture1);
    image.loadFromFile("Textures/guns/rocket_minigun/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[14].texture2.loadFromImage(image);
    guns[14].sprite2.setTexture(guns[14].texture2);
    image.loadFromFile("Textures/guns/rocket_minigun/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[14].texture3.loadFromImage(image);
    guns[14].sprite3.setTexture(guns[14].texture3);
    image.loadFromFile("Textures/guns/rocket_minigun/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[14].texture4.loadFromImage(image);
    guns[14].sprite4.setTexture(guns[14].texture4);
    guns[14].icon_texture.loadFromFile("Textures/guns/rocket_minigun/icon.png");
    guns[14].icon.setTexture(guns[14].icon_texture);
    image.loadFromFile("Textures/guns/rocket_minigun/proj1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[14].proj_texture1.loadFromImage(image);
    image.loadFromFile("Textures/guns/rocket_minigun/proj2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[14].proj_texture2.loadFromImage(image);
    image.loadFromFile("Textures/guns/rocket_minigun/proj3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[14].proj_texture3.loadFromImage(image);
    image.loadFromFile("Textures/guns/rocket_minigun/proj4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[14].proj_texture4.loadFromImage(image);
    image.loadFromFile("Textures/guns/rocket_minigun/blast.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[14].blast.loadFromImage(image);


    image.loadFromFile("Textures/guns/handgun/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[15].crosshair_texture.loadFromImage(image);
    guns[15].crosshair.setTexture(guns[15].crosshair_texture);
    image.loadFromFile("Textures/guns/handgun/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[15].texture1.loadFromImage(image);
    guns[15].sprite1.setTexture(guns[15].texture1);
    image.loadFromFile("Textures/guns/handgun/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[15].texture2.loadFromImage(image);
    guns[15].sprite2.setTexture(guns[15].texture2);
    image.loadFromFile("Textures/guns/handgun/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[15].texture3.loadFromImage(image);
    guns[15].sprite3.setTexture(guns[15].texture3);
    image.loadFromFile("Textures/guns/handgun/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[15].texture4.loadFromImage(image);
    guns[15].sprite4.setTexture(guns[15].texture4);
    guns[15].icon_texture.loadFromFile("Textures/guns/handgun/icon.png");
    guns[15].icon.setTexture(guns[15].icon_texture);
    image.loadFromFile("Textures/guns/handgun/proj1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[15].proj_texture1.loadFromImage(image);
    image.loadFromFile("Textures/guns/handgun/proj2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[15].proj_texture2.loadFromImage(image);
    image.loadFromFile("Textures/guns/handgun/proj3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[15].proj_texture3.loadFromImage(image);
    image.loadFromFile("Textures/guns/handgun/proj4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[15].proj_texture4.loadFromImage(image);
    image.loadFromFile("Textures/guns/handgun/blast.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[15].blast.loadFromImage(image);


    image.loadFromFile("Textures/guns/plasma/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[16].crosshair_texture.loadFromImage(image);
    guns[16].crosshair.setTexture(guns[16].crosshair_texture);
    image.loadFromFile("Textures/guns/plasma/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[16].texture1.loadFromImage(image);
    guns[16].sprite1.setTexture(guns[16].texture1);
    image.loadFromFile("Textures/guns/plasma/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[16].texture2.loadFromImage(image);
    guns[16].sprite2.setTexture(guns[16].texture2);
    image.loadFromFile("Textures/guns/plasma/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[16].texture3.loadFromImage(image);
    guns[16].sprite3.setTexture(guns[16].texture3);
    image.loadFromFile("Textures/guns/plasma/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[16].texture4.loadFromImage(image);
    guns[16].sprite4.setTexture(guns[16].texture4);
    guns[16].icon_texture.loadFromFile("Textures/guns/plasma/icon.png");
    guns[16].icon.setTexture(guns[16].icon_texture);
    image.loadFromFile("Textures/guns/plasma/proj1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[16].proj_texture1.loadFromImage(image);
    image.loadFromFile("Textures/guns/plasma/proj2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[16].proj_texture2.loadFromImage(image);
    image.loadFromFile("Textures/guns/plasma/proj3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[16].proj_texture3.loadFromImage(image);
    image.loadFromFile("Textures/guns/plasma/proj4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[16].proj_texture4.loadFromImage(image);
    image.loadFromFile("Textures/guns/plasma/blast.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[16].blast.loadFromImage(image);


    image.loadFromFile("Textures/guns/flamethrower/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[17].crosshair_texture.loadFromImage(image);
    guns[17].crosshair.setTexture(guns[17].crosshair_texture);
    image.loadFromFile("Textures/guns/flamethrower/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[17].texture1.loadFromImage(image);
    guns[17].sprite1.setTexture(guns[17].texture1);
    image.loadFromFile("Textures/guns/flamethrower/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[17].texture2.loadFromImage(image);
    guns[17].sprite2.setTexture(guns[17].texture2);
    image.loadFromFile("Textures/guns/flamethrower/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[17].texture3.loadFromImage(image);
    guns[17].sprite3.setTexture(guns[17].texture3);
    image.loadFromFile("Textures/guns/flamethrower/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[17].texture4.loadFromImage(image);
    guns[17].sprite4.setTexture(guns[17].texture4);
    guns[17].icon_texture.loadFromFile("Textures/guns/flamethrower/icon.png");
    guns[17].icon.setTexture(guns[17].icon_texture);
    image.loadFromFile("Textures/guns/flamethrower/proj1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[17].proj_texture1.loadFromImage(image);
    image.loadFromFile("Textures/guns/flamethrower/proj2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[17].proj_texture2.loadFromImage(image);
    image.loadFromFile("Textures/guns/flamethrower/proj3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[17].proj_texture3.loadFromImage(image);
    image.loadFromFile("Textures/guns/flamethrower/proj4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[17].proj_texture4.loadFromImage(image);
    image.loadFromFile("Textures/guns/flamethrower/blast.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[17].blast.loadFromImage(image);

    image.loadFromFile("Textures/guns/gauss/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[18].crosshair_texture.loadFromImage(image);
    guns[18].crosshair.setTexture(guns[18].crosshair_texture);
    guns[18].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[18].bullet.setTexture(guns[18].bullet_texture);
    image.loadFromFile("Textures/guns/gauss/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[18].texture1.loadFromImage(image);
    guns[18].sprite1.setTexture(guns[18].texture1);
    image.loadFromFile("Textures/guns/gauss/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[18].texture2.loadFromImage(image);
    guns[18].sprite2.setTexture(guns[18].texture2);
    image.loadFromFile("Textures/guns/gauss/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[18].texture3.loadFromImage(image);
    guns[18].sprite3.setTexture(guns[18].texture3);
    image.loadFromFile("Textures/guns/gauss/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[18].texture4.loadFromImage(image);
    guns[18].sprite4.setTexture(guns[18].texture4);
    guns[18].icon_texture.loadFromFile("Textures/guns/gauss/icon.png");
    guns[18].icon.setTexture(guns[18].icon_texture);


    image.loadFromFile("Textures/guns/laserpistol/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[19].crosshair_texture.loadFromImage(image);
    guns[19].crosshair.setTexture(guns[19].crosshair_texture);
    guns[19].bullet_texture.loadFromFile("Textures/blue_laser.png");
    guns[19].bullet.setTexture(guns[19].bullet_texture);
    image.loadFromFile("Textures/guns/laserpistol/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[19].texture1.loadFromImage(image);
    guns[19].sprite1.setTexture(guns[19].texture1);
    image.loadFromFile("Textures/guns/laserpistol/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[19].texture2.loadFromImage(image);
    guns[19].sprite2.setTexture(guns[19].texture2);
    image.loadFromFile("Textures/guns/laserpistol/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[19].texture3.loadFromImage(image);
    guns[19].sprite3.setTexture(guns[19].texture3);
    image.loadFromFile("Textures/guns/laserpistol/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[19].texture4.loadFromImage(image);
    guns[19].sprite4.setTexture(guns[19].texture4);
    guns[19].icon_texture.loadFromFile("Textures/guns/laserpistol/icon.png");
    guns[19].icon.setTexture(guns[19].icon_texture);


    image.loadFromFile("Textures/guns/goldenmg/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[20].crosshair_texture.loadFromImage(image);
    guns[20].crosshair.setTexture(guns[20].crosshair_texture);
    guns[20].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[20].bullet.setTexture(guns[20].bullet_texture);
    image.loadFromFile("Textures/guns/goldenmg/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[20].texture1.loadFromImage(image);
    guns[20].sprite1.setTexture(guns[20].texture1);
    image.loadFromFile("Textures/guns/goldenmg/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[20].texture2.loadFromImage(image);
    guns[20].sprite2.setTexture(guns[20].texture2);
    image.loadFromFile("Textures/guns/goldenmg/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[20].texture3.loadFromImage(image);
    guns[20].sprite3.setTexture(guns[20].texture3);
    image.loadFromFile("Textures/guns/goldenmg/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[20].texture4.loadFromImage(image);
    guns[20].sprite4.setTexture(guns[20].texture4);
    guns[20].icon_texture.loadFromFile("Textures/guns/goldenmg/icon.png");
    guns[20].icon.setTexture(guns[20].icon_texture);


    image.loadFromFile("Textures/guns/shotgun/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[21].crosshair_texture.loadFromImage(image);
    guns[21].crosshair.setTexture(guns[21].crosshair_texture);
    guns[21].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[21].bullet.setTexture(guns[21].bullet_texture);
    image.loadFromFile("Textures/guns/shotgun/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[21].texture1.loadFromImage(image);
    guns[21].sprite1.setTexture(guns[21].texture1);
    image.loadFromFile("Textures/guns/shotgun/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[21].texture2.loadFromImage(image);
    guns[21].sprite2.setTexture(guns[21].texture2);
    image.loadFromFile("Textures/guns/shotgun/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[21].texture3.loadFromImage(image);
    guns[21].sprite3.setTexture(guns[21].texture3);
    image.loadFromFile("Textures/guns/shotgun/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[21].texture4.loadFromImage(image);
    guns[21].sprite4.setTexture(guns[21].texture4);
    guns[21].icon_texture.loadFromFile("Textures/guns/shotgun/icon.png");
    guns[21].icon.setTexture(guns[21].icon_texture);


    image.loadFromFile("Textures/guns/optic/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[22].crosshair_texture.loadFromImage(image);
    guns[22].crosshair.setTexture(guns[22].crosshair_texture);
    guns[22].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[22].bullet.setTexture(guns[22].bullet_texture);
    image.loadFromFile("Textures/guns/optic/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[22].texture1.loadFromImage(image);
    guns[22].sprite1.setTexture(guns[22].texture1);
    image.loadFromFile("Textures/guns/optic/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[22].texture2.loadFromImage(image);
    guns[22].sprite2.setTexture(guns[22].texture2);
    image.loadFromFile("Textures/guns/optic/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[22].texture3.loadFromImage(image);
    guns[22].sprite3.setTexture(guns[22].texture3);
    image.loadFromFile("Textures/guns/optic/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[22].texture4.loadFromImage(image);
    guns[22].sprite4.setTexture(guns[22].texture4);
    guns[22].icon_texture.loadFromFile("Textures/guns/optic/icon.png");
    guns[22].icon.setTexture(guns[22].icon_texture);


    image.loadFromFile("Textures/guns/electric_arc/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[23].crosshair_texture.loadFromImage(image);
    guns[23].crosshair.setTexture(guns[23].crosshair_texture);
    image.loadFromFile("Textures/electricity.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[23].bullet_texture.loadFromImage(image);
    guns[23].bullet.setTexture(guns[23].bullet_texture);
    image.loadFromFile("Textures/guns/electric_arc/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[23].texture1.loadFromImage(image);
    guns[23].sprite1.setTexture(guns[23].texture1);
    image.loadFromFile("Textures/guns/electric_arc/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[23].texture2.loadFromImage(image);
    guns[23].sprite2.setTexture(guns[23].texture2);
    image.loadFromFile("Textures/guns/electric_arc/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[23].texture3.loadFromImage(image);
    guns[23].sprite3.setTexture(guns[23].texture3);
    image.loadFromFile("Textures/guns/electric_arc/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[23].texture4.loadFromImage(image);
    guns[23].sprite4.setTexture(guns[23].texture4);
    guns[23].icon_texture.loadFromFile("Textures/guns/electric_arc/icon.png");
    guns[23].icon.setTexture(guns[23].icon_texture);


    image.loadFromFile("Textures/guns/railgun/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[24].crosshair_texture.loadFromImage(image);
    guns[24].crosshair.setTexture(guns[24].crosshair_texture);
    guns[24].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[24].bullet.setTexture(guns[24].bullet_texture);
    image.loadFromFile("Textures/guns/railgun/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[24].texture1.loadFromImage(image);
    guns[24].sprite1.setTexture(guns[24].texture1);
    image.loadFromFile("Textures/guns/railgun/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[24].texture2.loadFromImage(image);
    guns[24].sprite2.setTexture(guns[24].texture2);
    image.loadFromFile("Textures/guns/railgun/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[24].texture3.loadFromImage(image);
    guns[24].sprite3.setTexture(guns[24].texture3);
    image.loadFromFile("Textures/guns/railgun/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[24].texture4.loadFromImage(image);
    guns[24].sprite4.setTexture(guns[24].texture4);
    guns[24].icon_texture.loadFromFile("Textures/guns/railgun/icon.png");
    guns[24].icon.setTexture(guns[24].icon_texture);


    image.loadFromFile("Textures/guns/zapper/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[25].crosshair_texture.loadFromImage(image);
    guns[25].crosshair.setTexture(guns[25].crosshair_texture);
    image.loadFromFile("Textures/guns/zapper/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[25].texture1.loadFromImage(image);
    guns[25].sprite1.setTexture(guns[25].texture1);
    image.loadFromFile("Textures/guns/zapper/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[25].texture2.loadFromImage(image);
    guns[25].sprite2.setTexture(guns[25].texture2);
    image.loadFromFile("Textures/guns/zapper/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[25].texture3.loadFromImage(image);
    guns[25].sprite3.setTexture(guns[25].texture3);
    image.loadFromFile("Textures/guns/zapper/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[25].texture4.loadFromImage(image);
    guns[25].sprite4.setTexture(guns[25].texture4);
    guns[25].icon_texture.loadFromFile("Textures/guns/zapper/icon.png");
    guns[25].icon.setTexture(guns[25].icon_texture);
    image.loadFromFile("Textures/guns/zapper/proj1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[25].proj_texture1.loadFromImage(image);
    image.loadFromFile("Textures/guns/zapper/proj2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[25].proj_texture2.loadFromImage(image);
    image.loadFromFile("Textures/guns/zapper/proj3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[25].proj_texture3.loadFromImage(image);
    image.loadFromFile("Textures/guns/zapper/proj4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[25].proj_texture4.loadFromImage(image);
    image.loadFromFile("Textures/blank.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[25].blast.loadFromImage(image);


    image.loadFromFile("Textures/guns/goldenpistol/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[26].crosshair_texture.loadFromImage(image);
    guns[26].crosshair.setTexture(guns[26].crosshair_texture);
    guns[26].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[26].bullet.setTexture(guns[26].bullet_texture);
    image.loadFromFile("Textures/guns/goldenpistol/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[26].texture1.loadFromImage(image);
    guns[26].sprite1.setTexture(guns[26].texture1);
    image.loadFromFile("Textures/guns/goldenpistol/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[26].texture2.loadFromImage(image);
    guns[26].sprite2.setTexture(guns[26].texture2);
    image.loadFromFile("Textures/guns/goldenpistol/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[26].texture3.loadFromImage(image);
    guns[26].sprite3.setTexture(guns[26].texture3);
    image.loadFromFile("Textures/guns/goldenpistol/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[26].texture4.loadFromImage(image);
    guns[26].sprite4.setTexture(guns[26].texture4);
    guns[26].icon_texture.loadFromFile("Textures/guns/goldenpistol/icon.png");
    guns[26].icon.setTexture(guns[26].icon_texture);


    image.loadFromFile("Textures/guns/mounted_sentry/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[27].crosshair_texture.loadFromImage(image);
    guns[27].crosshair.setTexture(guns[27].crosshair_texture);
    guns[27].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[27].bullet.setTexture(guns[27].bullet_texture);
    image.loadFromFile("Textures/guns/mounted_sentry/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[27].texture1.loadFromImage(image);
    guns[27].sprite1.setTexture(guns[27].texture1);
    image.loadFromFile("Textures/guns/mounted_sentry/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[27].texture2.loadFromImage(image);
    guns[27].sprite2.setTexture(guns[27].texture2);
    image.loadFromFile("Textures/guns/mounted_sentry/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[27].texture3.loadFromImage(image);
    guns[27].sprite3.setTexture(guns[27].texture3);
    image.loadFromFile("Textures/guns/mounted_sentry/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[27].texture4.loadFromImage(image);
    guns[27].sprite4.setTexture(guns[27].texture4);
    guns[27].icon_texture.loadFromFile("Textures/guns/mounted_sentry/icon.png");
    guns[27].icon.setTexture(guns[27].icon_texture);


    image.loadFromFile("Textures/guns/shotgun_uzi/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[28].crosshair_texture.loadFromImage(image);
    guns[28].crosshair.setTexture(guns[28].crosshair_texture);
    guns[28].bullet_texture.loadFromFile("Textures/bullet.png");
    guns[28].bullet.setTexture(guns[28].bullet_texture);
    image.loadFromFile("Textures/guns/shotgun_uzi/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[28].texture1.loadFromImage(image);
    guns[28].sprite1.setTexture(guns[28].texture1);
    image.loadFromFile("Textures/guns/shotgun_uzi/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[28].texture2.loadFromImage(image);
    guns[28].sprite2.setTexture(guns[28].texture2);
    image.loadFromFile("Textures/guns/shotgun_uzi/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[28].texture3.loadFromImage(image);
    guns[28].sprite3.setTexture(guns[28].texture3);
    image.loadFromFile("Textures/guns/shotgun_uzi/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[28].texture4.loadFromImage(image);
    guns[28].sprite4.setTexture(guns[28].texture4);
    guns[28].icon_texture.loadFromFile("Textures/guns/shotgun_uzi/icon.png");
    guns[28].icon.setTexture(guns[28].icon_texture);


    image.loadFromFile("Textures/guns/boosty&speedy/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[29].crosshair_texture.loadFromImage(image);
    guns[29].crosshair.setTexture(guns[29].crosshair_texture);
    guns[29].bullet_texture.loadFromFile("Textures/blue_laser.png");
    guns[29].bullet.setTexture(guns[29].bullet_texture);
    image.loadFromFile("Textures/guns/boosty&speedy/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[29].texture1.loadFromImage(image);
    guns[29].sprite1.setTexture(guns[29].texture1);
    image.loadFromFile("Textures/guns/boosty&speedy/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[29].texture2.loadFromImage(image);
    guns[29].sprite2.setTexture(guns[29].texture2);
    image.loadFromFile("Textures/guns/boosty&speedy/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[29].texture3.loadFromImage(image);
    guns[29].sprite3.setTexture(guns[29].texture3);
    image.loadFromFile("Textures/guns/boosty&speedy/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[29].texture4.loadFromImage(image);
    guns[29].sprite4.setTexture(guns[29].texture4);
    guns[29].icon_texture.loadFromFile("Textures/guns/boosty&speedy/icon.png");
    guns[29].icon.setTexture(guns[29].icon_texture);


    image.loadFromFile("Textures/guns/plasma_shotgun/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[30].crosshair_texture.loadFromImage(image);
    guns[30].crosshair.setTexture(guns[30].crosshair_texture);
    image.loadFromFile("Textures/guns/plasma_shotgun/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[30].texture1.loadFromImage(image);
    guns[30].sprite1.setTexture(guns[30].texture1);
    image.loadFromFile("Textures/guns/plasma_shotgun/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[30].texture2.loadFromImage(image);
    guns[30].sprite2.setTexture(guns[30].texture2);
    image.loadFromFile("Textures/guns/plasma_shotgun/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[30].texture3.loadFromImage(image);
    guns[30].sprite3.setTexture(guns[30].texture3);
    image.loadFromFile("Textures/guns/plasma_shotgun/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[30].texture4.loadFromImage(image);
    guns[30].sprite4.setTexture(guns[30].texture4);
    guns[30].icon_texture.loadFromFile("Textures/guns/plasma_shotgun/icon.png");
    guns[30].icon.setTexture(guns[30].icon_texture);
    image.loadFromFile("Textures/guns/plasma/proj1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[30].proj_texture1.loadFromImage(image);
    image.loadFromFile("Textures/guns/plasma/proj2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[30].proj_texture2.loadFromImage(image);
    image.loadFromFile("Textures/guns/plasma/proj3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[30].proj_texture3.loadFromImage(image);
    image.loadFromFile("Textures/guns/plasma/proj4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[30].proj_texture4.loadFromImage(image);
    image.loadFromFile("Textures/guns/plasma/blast.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[30].blast.loadFromImage(image);


    image.loadFromFile("Textures/guns/rocket_launcher/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[31].crosshair_texture.loadFromImage(image);
    guns[31].crosshair.setTexture(guns[31].crosshair_texture);
    image.loadFromFile("Textures/guns/rocket_launcher/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[31].texture1.loadFromImage(image);
    guns[31].sprite1.setTexture(guns[31].texture1);
    image.loadFromFile("Textures/guns/rocket_launcher/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[31].texture2.loadFromImage(image);
    guns[31].sprite2.setTexture(guns[31].texture2);
    image.loadFromFile("Textures/guns/rocket_launcher/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[31].texture3.loadFromImage(image);
    guns[31].sprite3.setTexture(guns[31].texture3);
    image.loadFromFile("Textures/guns/rocket_launcher/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[31].texture4.loadFromImage(image);
    guns[31].sprite4.setTexture(guns[31].texture4);
    guns[31].icon_texture.loadFromFile("Textures/guns/rocket_launcher/icon.png");
    guns[31].icon.setTexture(guns[31].icon_texture);
    image.loadFromFile("Textures/guns/rocket_launcher/proj1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[31].proj_texture1.loadFromImage(image);
    image.loadFromFile("Textures/guns/rocket_launcher/proj2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[31].proj_texture2.loadFromImage(image);
    image.loadFromFile("Textures/guns/rocket_launcher/proj3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[31].proj_texture3.loadFromImage(image);
    image.loadFromFile("Textures/guns/rocket_launcher/proj4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[31].proj_texture4.loadFromImage(image);
    image.loadFromFile("Textures/guns/rocket_launcher/blast.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[31].blast.loadFromImage(image);


    image.loadFromFile("Textures/guns/tesla_rifle/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[32].crosshair_texture.loadFromImage(image);
    guns[32].crosshair.setTexture(guns[32].crosshair_texture);
    image.loadFromFile("Textures/guns/tesla_rifle/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[32].texture1.loadFromImage(image);
    guns[32].sprite1.setTexture(guns[32].texture1);
    image.loadFromFile("Textures/guns/tesla_rifle/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[32].texture2.loadFromImage(image);
    guns[32].sprite2.setTexture(guns[32].texture2);
    image.loadFromFile("Textures/guns/tesla_rifle/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[32].texture3.loadFromImage(image);
    guns[32].sprite3.setTexture(guns[32].texture3);
    image.loadFromFile("Textures/guns/tesla_rifle/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[32].texture4.loadFromImage(image);
    guns[32].sprite4.setTexture(guns[32].texture4);
    guns[32].icon_texture.loadFromFile("Textures/guns/tesla_rifle/icon.png");
    guns[32].icon.setTexture(guns[32].icon_texture);
    image.loadFromFile("Textures/guns/tesla_rifle/proj1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[32].proj_texture1.loadFromImage(image);
    image.loadFromFile("Textures/guns/tesla_rifle/proj2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[32].proj_texture2.loadFromImage(image);
    image.loadFromFile("Textures/guns/tesla_rifle/proj3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[32].proj_texture3.loadFromImage(image);
    image.loadFromFile("Textures/guns/tesla_rifle/proj4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[32].proj_texture4.loadFromImage(image);
    image.loadFromFile("Textures/guns/tesla_rifle/blast.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[32].blast.loadFromImage(image);


    image.loadFromFile("Textures/guns/gatling/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[33].crosshair_texture.loadFromImage(image);
    guns[33].crosshair.setTexture(guns[33].crosshair_texture);
    image.loadFromFile("Textures/gatling_bullet.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[33].bullet_texture.loadFromImage(image);
    guns[33].bullet.setTexture(guns[33].bullet_texture);
    image.loadFromFile("Textures/guns/gatling/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[33].texture1.loadFromImage(image);
    guns[33].sprite1.setTexture(guns[33].texture1);
    image.loadFromFile("Textures/guns/gatling/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[33].texture2.loadFromImage(image);
    guns[33].sprite2.setTexture(guns[33].texture2);
    image.loadFromFile("Textures/guns/gatling/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[33].texture3.loadFromImage(image);
    guns[33].sprite3.setTexture(guns[33].texture3);
    image.loadFromFile("Textures/guns/gatling/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[33].texture4.loadFromImage(image);
    guns[33].sprite4.setTexture(guns[33].texture4);
    guns[33].icon_texture.loadFromFile("Textures/guns/gatling/icon.png");
    guns[33].icon.setTexture(guns[33].icon_texture);



    image.loadFromFile("Textures/guns/knife/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[34].crosshair_texture.loadFromImage(image);
    guns[34].crosshair.setTexture(guns[34].crosshair_texture);
    image.loadFromFile("Textures/blank.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[34].bullet_texture.loadFromImage(image);
    guns[34].bullet.setTexture(guns[34].bullet_texture);
    image.loadFromFile("Textures/guns/knife/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[34].texture1.loadFromImage(image);
    guns[34].sprite1.setTexture(guns[34].texture1);
    image.loadFromFile("Textures/guns/knife/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[34].texture2.loadFromImage(image);
    guns[34].sprite2.setTexture(guns[34].texture2);
    image.loadFromFile("Textures/guns/knife/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[34].texture3.loadFromImage(image);
    guns[34].sprite3.setTexture(guns[34].texture3);
    image.loadFromFile("Textures/guns/knife/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[34].texture4.loadFromImage(image);
    guns[34].sprite4.setTexture(guns[34].texture4);
    guns[34].icon_texture.loadFromFile("Textures/guns/knife/icon.png");
    guns[34].icon.setTexture(guns[34].icon_texture);


    image.loadFromFile("Textures/guns/skeleton/crosshair.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[35].crosshair_texture.loadFromImage(image);
    guns[35].crosshair.setTexture(guns[35].crosshair_texture);
    image.loadFromFile("Textures/blue_laser.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[35].bullet_texture.loadFromImage(image);
    guns[35].bullet.setTexture(guns[35].bullet_texture);
    image.loadFromFile("Textures/guns/skeleton/image1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[35].texture1.loadFromImage(image);
    guns[35].sprite1.setTexture(guns[35].texture1);
    image.loadFromFile("Textures/guns/skeleton/image2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[35].texture2.loadFromImage(image);
    guns[35].sprite2.setTexture(guns[35].texture2);
    image.loadFromFile("Textures/guns/skeleton/image3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[35].texture3.loadFromImage(image);
    guns[35].sprite3.setTexture(guns[35].texture3);
    image.loadFromFile("Textures/guns/skeleton/image4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    guns[35].texture4.loadFromImage(image);
    guns[35].sprite4.setTexture(guns[35].texture4);
    guns[35].icon_texture.loadFromFile("Textures/guns/skeleton/icon.png");
    guns[35].icon.setTexture(guns[35].icon_texture);

    //
    /*image.loadFromFile("Textures/guns/machine_gun/right_hand1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[0].right_texture1.loadFromImage(image);
    player.hands[0].right1.setTexture(player.hands[0].right_texture1);
    image.loadFromFile("Textures/guns/machine_gun/right_hand2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[0].right_texture2.loadFromImage(image);
    player.hands[0].right2.setTexture(player.hands[0].right_texture2);
    image.loadFromFile("Textures/guns/machine_gun/right_hand3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[0].right_texture3.loadFromImage(image);
    player.hands[0].right3.setTexture(player.hands[0].right_texture3);
    image.loadFromFile("Textures/guns/machine_gun/right_hand4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[0].right_texture4.loadFromImage(image);
    player.hands[0].right4.setTexture(player.hands[0].right_texture4);
    image.loadFromFile("Textures/guns/machine_gun/left_hand1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[0].left_texture1.loadFromImage(image);
    player.hands[0].left1.setTexture(player.hands[0].left_texture1);
    image.loadFromFile("Textures/guns/machine_gun/left_hand2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[0].left_texture2.loadFromImage(image);
    player.hands[0].left2.setTexture(player.hands[0].left_texture2);
    image.loadFromFile("Textures/guns/machine_gun/left_hand3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[0].left_texture3.loadFromImage(image);
    player.hands[0].left3.setTexture(player.hands[0].left_texture3);
    image.loadFromFile("Textures/guns/machine_gun/left_hand4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[0].left_texture4.loadFromImage(image);
    player.hands[0].left4.setTexture(player.hands[0].left_texture4);*/


    /*image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[1].right_texture1.loadFromImage(image);
    player.hands[1].right1.setTexture(player.hands[1].right_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[1].right_texture2.loadFromImage(image);
    player.hands[1].right2.setTexture(player.hands[1].right_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[1].right_texture3.loadFromImage(image);
    player.hands[1].right3.setTexture(player.hands[1].right_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[1].right_texture4.loadFromImage(image);
    player.hands[1].right4.setTexture(player.hands[1].right_texture4);
    image.loadFromFile("Textures/guns/pistol/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[1].left_texture1.loadFromImage(image);
    player.hands[1].left1.setTexture(player.hands[1].left_texture1);
    image.loadFromFile("Textures/guns/pistol/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[1].left_texture2.loadFromImage(image);
    player.hands[1].left2.setTexture(player.hands[1].left_texture2);
    image.loadFromFile("Textures/guns/pistol/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[1].left_texture3.loadFromImage(image);
    player.hands[1].left3.setTexture(player.hands[1].left_texture3);
    image.loadFromFile("Textures/guns/pistol/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[1].left_texture4.loadFromImage(image);
    player.hands[1].left4.setTexture(player.hands[1].left_texture4);


    image.loadFromFile("Textures/guns/sandgun/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[2].right_texture1.loadFromImage(image);
    player.hands[2].right1.setTexture(player.hands[2].right_texture1);
    image.loadFromFile("Textures/guns/sandgun/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[2].right_texture2.loadFromImage(image);
    player.hands[2].right2.setTexture(player.hands[2].right_texture2);
    image.loadFromFile("Textures/guns/sandgun/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[2].right_texture3.loadFromImage(image);
    player.hands[2].right3.setTexture(player.hands[2].right_texture3);
    image.loadFromFile("Textures/guns/sandgun/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[2].right_texture4.loadFromImage(image);
    player.hands[2].right4.setTexture(player.hands[2].right_texture4);
    image.loadFromFile("Textures/guns/sandgun/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[2].left_texture1.loadFromImage(image);
    player.hands[2].left1.setTexture(player.hands[2].left_texture1);
    image.loadFromFile("Textures/guns/sandgun/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[2].left_texture2.loadFromImage(image);
    player.hands[2].left2.setTexture(player.hands[2].left_texture2);
    image.loadFromFile("Textures/guns/sandgun/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[2].left_texture3.loadFromImage(image);
    player.hands[2].left3.setTexture(player.hands[2].left_texture3);
    image.loadFromFile("Textures/guns/sandgun/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[2].left_texture4.loadFromImage(image);
    player.hands[2].left4.setTexture(player.hands[2].left_texture4);


    image.loadFromFile("Textures/guns/lever_action/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[3].right_texture1.loadFromImage(image);
    player.hands[3].right1.setTexture(player.hands[3].right_texture1);
    image.loadFromFile("Textures/guns/lever_action/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[3].right_texture2.loadFromImage(image);
    player.hands[3].right2.setTexture(player.hands[3].right_texture2);
    image.loadFromFile("Textures/guns/lever_action/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[3].right_texture3.loadFromImage(image);
    player.hands[3].right3.setTexture(player.hands[3].right_texture3);
    image.loadFromFile("Textures/guns/lever_action/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[3].right_texture4.loadFromImage(image);
    player.hands[3].right4.setTexture(player.hands[3].right_texture4);
    image.loadFromFile("Textures/guns/lever_action/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[3].left_texture1.loadFromImage(image);
    player.hands[3].left1.setTexture(player.hands[3].left_texture1);
    image.loadFromFile("Textures/guns/lever_action/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[3].left_texture2.loadFromImage(image);
    player.hands[3].left2.setTexture(player.hands[3].left_texture2);
    image.loadFromFile("Textures/guns/lever_action/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[3].left_texture3.loadFromImage(image);
    player.hands[3].left3.setTexture(player.hands[3].left_texture3);
    image.loadFromFile("Textures/guns/lever_action/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[3].left_texture4.loadFromImage(image);
    player.hands[3].left4.setTexture(player.hands[3].left_texture4);


    image.loadFromFile("Textures/guns/laser_rifle/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[4].right_texture1.loadFromImage(image);
    player.hands[4].right1.setTexture(player.hands[4].right_texture1);
    image.loadFromFile("Textures/guns/laser_rifle/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[4].right_texture2.loadFromImage(image);
    player.hands[4].right2.setTexture(player.hands[4].right_texture2);
    image.loadFromFile("Textures/guns/laser_rifle/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[4].right_texture3.loadFromImage(image);
    player.hands[4].right3.setTexture(player.hands[4].right_texture3);
    image.loadFromFile("Textures/guns/laser_rifle/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[4].right_texture4.loadFromImage(image);
    player.hands[4].right4.setTexture(player.hands[4].right_texture4);
    image.loadFromFile("Textures/guns/laser_rifle/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[4].left_texture1.loadFromImage(image);
    player.hands[4].left1.setTexture(player.hands[4].left_texture1);
    image.loadFromFile("Textures/guns/laser_rifle/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[4].left_texture2.loadFromImage(image);
    player.hands[4].left2.setTexture(player.hands[4].left_texture2);
    image.loadFromFile("Textures/guns/laser_rifle/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[4].left_texture3.loadFromImage(image);
    player.hands[4].left3.setTexture(player.hands[4].left_texture3);
    image.loadFromFile("Textures/guns/laser_rifle/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[4].left_texture4.loadFromImage(image);
    player.hands[4].left4.setTexture(player.hands[4].left_texture4);


    image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[5].right_texture1.loadFromImage(image);
    player.hands[5].right1.setTexture(player.hands[5].right_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[5].right_texture2.loadFromImage(image);
    player.hands[5].right2.setTexture(player.hands[5].right_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[5].right_texture3.loadFromImage(image);
    player.hands[5].right3.setTexture(player.hands[5].right_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[5].right_texture4.loadFromImage(image);
    player.hands[5].right4.setTexture(player.hands[5].right_texture4);
    image.loadFromFile("Textures/guns/pistol/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[5].left_texture1.loadFromImage(image);
    player.hands[5].left1.setTexture(player.hands[5].left_texture1);
    image.loadFromFile("Textures/guns/pistol/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[5].left_texture2.loadFromImage(image);
    player.hands[5].left2.setTexture(player.hands[5].left_texture2);
    image.loadFromFile("Textures/guns/pistol/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[5].left_texture3.loadFromImage(image);
    player.hands[5].left3.setTexture(player.hands[5].left_texture3);
    image.loadFromFile("Textures/guns/pistol/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[5].left_texture4.loadFromImage(image);
    player.hands[5].left4.setTexture(player.hands[5].left_texture4);


    image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[6].right_texture1.loadFromImage(image);
    player.hands[6].right1.setTexture(player.hands[6].right_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[6].right_texture2.loadFromImage(image);
    player.hands[6].right2.setTexture(player.hands[6].right_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[6].right_texture3.loadFromImage(image);
    player.hands[6].right3.setTexture(player.hands[6].right_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[6].right_texture4.loadFromImage(image);
    player.hands[6].right4.setTexture(player.hands[6].right_texture4);
    image.loadFromFile("Textures/guns/pistol/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[6].left_texture1.loadFromImage(image);
    player.hands[6].left1.setTexture(player.hands[6].left_texture1);
    image.loadFromFile("Textures/guns/pistol/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[6].left_texture2.loadFromImage(image);
    player.hands[6].left2.setTexture(player.hands[6].left_texture2);
    image.loadFromFile("Textures/guns/pistol/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[6].left_texture3.loadFromImage(image);
    player.hands[6].left3.setTexture(player.hands[6].left_texture3);
    image.loadFromFile("Textures/guns/pistol/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[6].left_texture4.loadFromImage(image);
    player.hands[6].left4.setTexture(player.hands[6].left_texture4);


    image.loadFromFile("Textures/guns/smg/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[7].right_texture1.loadFromImage(image);
    player.hands[7].right1.setTexture(player.hands[7].right_texture1);
    image.loadFromFile("Textures/guns/smg/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[7].right_texture2.loadFromImage(image);
    player.hands[7].right2.setTexture(player.hands[7].right_texture2);
    image.loadFromFile("Textures/guns/smg/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[7].right_texture3.loadFromImage(image);
    player.hands[7].right3.setTexture(player.hands[7].right_texture3);
    image.loadFromFile("Textures/guns/smg/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[7].right_texture4.loadFromImage(image);
    player.hands[7].right4.setTexture(player.hands[7].right_texture4);
    image.loadFromFile("Textures/guns/smg/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[7].left_texture1.loadFromImage(image);
    player.hands[7].left1.setTexture(player.hands[7].left_texture1);
    image.loadFromFile("Textures/guns/smg/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[7].left_texture2.loadFromImage(image);
    player.hands[7].left2.setTexture(player.hands[7].left_texture2);
    image.loadFromFile("Textures/guns/smg/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[7].left_texture3.loadFromImage(image);
    player.hands[7].left3.setTexture(player.hands[7].left_texture3);
    image.loadFromFile("Textures/guns/smg/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[7].left_texture4.loadFromImage(image);
    player.hands[7].left4.setTexture(player.hands[7].left_texture4);


    image.loadFromFile("Textures/guns/laser_rifle/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[8].right_texture1.loadFromImage(image);
    player.hands[8].right1.setTexture(player.hands[8].right_texture1);
    image.loadFromFile("Textures/guns/laser_rifle/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[8].right_texture2.loadFromImage(image);
    player.hands[8].right2.setTexture(player.hands[8].right_texture2);
    image.loadFromFile("Textures/guns/laser_rifle/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[8].right_texture3.loadFromImage(image);
    player.hands[8].right3.setTexture(player.hands[8].right_texture3);
    image.loadFromFile("Textures/guns/laser_rifle/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[8].right_texture4.loadFromImage(image);
    player.hands[8].right4.setTexture(player.hands[8].right_texture4);
    image.loadFromFile("Textures/guns/laser_rifle/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[8].left_texture1.loadFromImage(image);
    player.hands[8].left1.setTexture(player.hands[8].left_texture1);
    image.loadFromFile("Textures/guns/laser_rifle/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[8].left_texture2.loadFromImage(image);
    player.hands[8].left2.setTexture(player.hands[8].left_texture2);
    image.loadFromFile("Textures/guns/laser_rifle/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[8].left_texture3.loadFromImage(image);
    player.hands[8].left3.setTexture(player.hands[8].left_texture3);
    image.loadFromFile("Textures/guns/laser_rifle/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[8].left_texture4.loadFromImage(image);
    player.hands[8].left4.setTexture(player.hands[8].left_texture4);


    image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[9].right_texture1.loadFromImage(image);
    player.hands[9].right1.setTexture(player.hands[9].right_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[9].right_texture2.loadFromImage(image);
    player.hands[9].right2.setTexture(player.hands[9].right_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[9].right_texture3.loadFromImage(image);
    player.hands[9].right3.setTexture(player.hands[9].right_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[9].right_texture4.loadFromImage(image);
    player.hands[9].right4.setTexture(player.hands[9].right_texture4);
    image.loadFromFile("Textures/guns/pistol/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[9].left_texture1.loadFromImage(image);
    player.hands[9].left1.setTexture(player.hands[9].left_texture1);
    image.loadFromFile("Textures/guns/pistol/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[9].left_texture2.loadFromImage(image);
    player.hands[9].left2.setTexture(player.hands[9].left_texture2);
    image.loadFromFile("Textures/guns/pistol/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[9].left_texture3.loadFromImage(image);
    player.hands[9].left3.setTexture(player.hands[9].left_texture3);
    image.loadFromFile("Textures/guns/pistol/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[9].left_texture4.loadFromImage(image);
    player.hands[9].left4.setTexture(player.hands[9].left_texture4);



    image.loadFromFile("Textures/guns/flintlock/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[10].right_texture1.loadFromImage(image);
    player.hands[10].right1.setTexture(player.hands[10].right_texture1);
    image.loadFromFile("Textures/guns/flintlock/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[10].right_texture2.loadFromImage(image);
    player.hands[10].right2.setTexture(player.hands[10].right_texture2);
    image.loadFromFile("Textures/guns/flintlock/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[10].right_texture3.loadFromImage(image);
    player.hands[10].right3.setTexture(player.hands[10].right_texture3);
    image.loadFromFile("Textures/guns/flintlock/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[10].right_texture4.loadFromImage(image);
    player.hands[10].right4.setTexture(player.hands[10].right_texture4);
    image.loadFromFile("Textures/guns/flintlock/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[10].left_texture1.loadFromImage(image);
    player.hands[10].left1.setTexture(player.hands[10].left_texture1);
    image.loadFromFile("Textures/guns/flintlock/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[10].left_texture2.loadFromImage(image);
    player.hands[10].left2.setTexture(player.hands[10].left_texture2);
    image.loadFromFile("Textures/guns/flintlock/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[10].left_texture3.loadFromImage(image);
    player.hands[10].left3.setTexture(player.hands[10].left_texture3);
    image.loadFromFile("Textures/guns/flintlock/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[10].left_texture4.loadFromImage(image);
    player.hands[10].left4.setTexture(player.hands[10].left_texture4);

    image.loadFromFile("Textures/guns/double/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[11].right_texture1.loadFromImage(image);
    player.hands[11].right1.setTexture(player.hands[11].right_texture1);
    image.loadFromFile("Textures/guns/double/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[11].right_texture2.loadFromImage(image);
    player.hands[11].right2.setTexture(player.hands[11].right_texture2);
    image.loadFromFile("Textures/guns/double/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[11].right_texture3.loadFromImage(image);
    player.hands[11].right3.setTexture(player.hands[11].right_texture3);
    image.loadFromFile("Textures/guns/double/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[11].right_texture4.loadFromImage(image);
    player.hands[11].right4.setTexture(player.hands[11].right_texture4);
    image.loadFromFile("Textures/guns/double/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[11].left_texture1.loadFromImage(image);
    player.hands[11].left1.setTexture(player.hands[11].left_texture1);
    image.loadFromFile("Textures/guns/double/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[11].left_texture2.loadFromImage(image);
    player.hands[11].left2.setTexture(player.hands[11].left_texture2);
    image.loadFromFile("Textures/guns/double/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[11].left_texture3.loadFromImage(image);
    player.hands[11].left3.setTexture(player.hands[11].left_texture3);
    image.loadFromFile("Textures/guns/double/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[11].left_texture4.loadFromImage(image);
    player.hands[11].left4.setTexture(player.hands[11].left_texture4);

    image.loadFromFile("Textures/guns/machine_gun/right_hand1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[12].right_texture1.loadFromImage(image);
    player.hands[12].right1.setTexture(player.hands[12].right_texture1);
    image.loadFromFile("Textures/guns/machine_gun/right_hand2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[12].right_texture2.loadFromImage(image);
    player.hands[12].right2.setTexture(player.hands[12].right_texture2);
    image.loadFromFile("Textures/guns/machine_gun/right_hand3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[12].right_texture3.loadFromImage(image);
    player.hands[12].right3.setTexture(player.hands[12].right_texture3);
    image.loadFromFile("Textures/guns/machine_gun/right_hand4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[12].right_texture4.loadFromImage(image);
    player.hands[12].right4.setTexture(player.hands[12].right_texture4);
    image.loadFromFile("Textures/guns/machine_gun/left_hand1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[12].left_texture1.loadFromImage(image);
    player.hands[12].left1.setTexture(player.hands[12].left_texture1);
    image.loadFromFile("Textures/guns/machine_gun/left_hand2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[12].left_texture2.loadFromImage(image);
    player.hands[12].left2.setTexture(player.hands[12].left_texture2);
    image.loadFromFile("Textures/guns/machine_gun/left_hand3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[12].left_texture3.loadFromImage(image);
    player.hands[12].left3.setTexture(player.hands[12].left_texture3);
    image.loadFromFile("Textures/guns/machine_gun/left_hand4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[12].left_texture4.loadFromImage(image);
    player.hands[12].left4.setTexture(player.hands[12].left_texture4);

    image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[13].right_texture1.loadFromImage(image);
    player.hands[13].right1.setTexture(player.hands[13].right_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[13].right_texture2.loadFromImage(image);
    player.hands[13].right2.setTexture(player.hands[13].right_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[13].right_texture3.loadFromImage(image);
    player.hands[13].right3.setTexture(player.hands[13].right_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[13].right_texture4.loadFromImage(image);
    player.hands[13].right4.setTexture(player.hands[13].right_texture4);
    image.loadFromFile("Textures/guns/machine_gun/left_hand1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[13].left_texture1.loadFromImage(image);
    player.hands[13].left1.setTexture(player.hands[13].left_texture1);
    image.loadFromFile("Textures/guns/machine_gun/left_hand2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[13].left_texture2.loadFromImage(image);
    player.hands[13].left2.setTexture(player.hands[13].left_texture2);
    image.loadFromFile("Textures/guns/machine_gun/left_hand3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[13].left_texture3.loadFromImage(image);
    player.hands[13].left3.setTexture(player.hands[13].left_texture3);
    image.loadFromFile("Textures/guns/machine_gun/left_hand4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[13].left_texture4.loadFromImage(image);
    player.hands[13].left4.setTexture(player.hands[13].left_texture4);

    image.loadFromFile("Textures/guns/rocket_minigun/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[14].right_texture1.loadFromImage(image);
    player.hands[14].right1.setTexture(player.hands[14].right_texture1);
    image.loadFromFile("Textures/guns/rocket_minigun/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[14].right_texture2.loadFromImage(image);
    player.hands[14].right2.setTexture(player.hands[14].right_texture2);
    image.loadFromFile("Textures/guns/rocket_minigun/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[14].right_texture3.loadFromImage(image);
    player.hands[14].right3.setTexture(player.hands[14].right_texture3);
    image.loadFromFile("Textures/guns/rocket_minigun/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[14].right_texture4.loadFromImage(image);
    player.hands[14].right4.setTexture(player.hands[14].right_texture4);
    image.loadFromFile("Textures/guns/rocket_minigun/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[14].left_texture1.loadFromImage(image);
    player.hands[14].left1.setTexture(player.hands[14].left_texture1);
    image.loadFromFile("Textures/guns/rocket_minigun/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[14].left_texture2.loadFromImage(image);
    player.hands[14].left2.setTexture(player.hands[14].left_texture2);
    image.loadFromFile("Textures/guns/rocket_minigun/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[14].left_texture3.loadFromImage(image);
    player.hands[14].left3.setTexture(player.hands[14].left_texture3);
    image.loadFromFile("Textures/guns/rocket_minigun/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[14].left_texture4.loadFromImage(image);
    player.hands[14].left4.setTexture(player.hands[14].left_texture4);

    image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[15].right_texture1.loadFromImage(image);
    player.hands[15].right1.setTexture(player.hands[15].right_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[15].right_texture2.loadFromImage(image);
    player.hands[15].right2.setTexture(player.hands[15].right_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[15].right_texture3.loadFromImage(image);
    player.hands[15].right3.setTexture(player.hands[15].right_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[15].right_texture4.loadFromImage(image);
    player.hands[15].right4.setTexture(player.hands[15].right_texture4);
    image.loadFromFile("Textures/guns/handgun/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[15].left_texture1.loadFromImage(image);
    player.hands[15].left1.setTexture(player.hands[15].left_texture1);
    image.loadFromFile("Textures/guns/handgun/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[15].left_texture2.loadFromImage(image);
    player.hands[15].left2.setTexture(player.hands[15].left_texture2);
    image.loadFromFile("Textures/guns/handgun/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[15].left_texture3.loadFromImage(image);
    player.hands[15].left3.setTexture(player.hands[15].left_texture3);
    image.loadFromFile("Textures/guns/handgun/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[15].left_texture4.loadFromImage(image);
    player.hands[15].left4.setTexture(player.hands[15].left_texture4);

    image.loadFromFile("Textures/guns/machine_gun/right_hand1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[16].right_texture1.loadFromImage(image);
    player.hands[16].right1.setTexture(player.hands[16].right_texture1);
    image.loadFromFile("Textures/guns/machine_gun/right_hand2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[16].right_texture2.loadFromImage(image);
    player.hands[16].right2.setTexture(player.hands[16].right_texture2);
    image.loadFromFile("Textures/guns/machine_gun/right_hand3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[16].right_texture3.loadFromImage(image);
    player.hands[16].right3.setTexture(player.hands[16].right_texture3);
    image.loadFromFile("Textures/guns/machine_gun/right_hand4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[16].right_texture4.loadFromImage(image);
    player.hands[16].right4.setTexture(player.hands[16].right_texture4);
    image.loadFromFile("Textures/guns/machine_gun/left_hand1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[16].left_texture1.loadFromImage(image);
    player.hands[16].left1.setTexture(player.hands[16].left_texture1);
    image.loadFromFile("Textures/guns/machine_gun/left_hand2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[16].left_texture2.loadFromImage(image);
    player.hands[16].left2.setTexture(player.hands[16].left_texture2);
    image.loadFromFile("Textures/guns/machine_gun/left_hand3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[16].left_texture3.loadFromImage(image);
    player.hands[16].left3.setTexture(player.hands[16].left_texture3);
    image.loadFromFile("Textures/guns/machine_gun/left_hand4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[16].left_texture4.loadFromImage(image);
    player.hands[16].left4.setTexture(player.hands[16].left_texture4);

    image.loadFromFile("Textures/guns/rocket_minigun/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[17].right_texture1.loadFromImage(image);
    player.hands[17].right1.setTexture(player.hands[17].right_texture1);
    image.loadFromFile("Textures/guns/rocket_minigun/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[17].right_texture2.loadFromImage(image);
    player.hands[17].right2.setTexture(player.hands[17].right_texture2);
    image.loadFromFile("Textures/guns/rocket_minigun/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[17].right_texture3.loadFromImage(image);
    player.hands[17].right3.setTexture(player.hands[17].right_texture3);
    image.loadFromFile("Textures/guns/rocket_minigun/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[17].right_texture4.loadFromImage(image);
    player.hands[17].right4.setTexture(player.hands[17].right_texture4);
    image.loadFromFile("Textures/guns/rocket_minigun/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[17].left_texture1.loadFromImage(image);
    player.hands[17].left1.setTexture(player.hands[17].left_texture1);
    image.loadFromFile("Textures/guns/rocket_minigun/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[17].left_texture2.loadFromImage(image);
    player.hands[17].left2.setTexture(player.hands[17].left_texture2);
    image.loadFromFile("Textures/guns/rocket_minigun/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[17].left_texture3.loadFromImage(image);
    player.hands[17].left3.setTexture(player.hands[17].left_texture3);
    image.loadFromFile("Textures/guns/rocket_minigun/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[17].left_texture4.loadFromImage(image);
    player.hands[17].left4.setTexture(player.hands[17].left_texture4);

    image.loadFromFile("Textures/guns/sandgun/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[18].right_texture1.loadFromImage(image);
    player.hands[18].right1.setTexture(player.hands[18].right_texture1);
    image.loadFromFile("Textures/guns/sandgun/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[18].right_texture2.loadFromImage(image);
    player.hands[18].right2.setTexture(player.hands[18].right_texture2);
    image.loadFromFile("Textures/guns/sandgun/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[18].right_texture3.loadFromImage(image);
    player.hands[18].right3.setTexture(player.hands[18].right_texture3);
    image.loadFromFile("Textures/guns/sandgun/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[18].right_texture4.loadFromImage(image);
    player.hands[18].right4.setTexture(player.hands[18].right_texture4);
    image.loadFromFile("Textures/guns/sandgun/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[18].left_texture1.loadFromImage(image);
    player.hands[18].left1.setTexture(player.hands[18].left_texture1);
    image.loadFromFile("Textures/guns/sandgun/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[18].left_texture2.loadFromImage(image);
    player.hands[18].left2.setTexture(player.hands[18].left_texture2);
    image.loadFromFile("Textures/guns/sandgun/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[18].left_texture3.loadFromImage(image);
    player.hands[18].left3.setTexture(player.hands[18].left_texture3);
    image.loadFromFile("Textures/guns/sandgun/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[18].left_texture4.loadFromImage(image);
    player.hands[18].left4.setTexture(player.hands[18].left_texture4);


    image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[19].right_texture1.loadFromImage(image);
    player.hands[19].right1.setTexture(player.hands[19].right_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[19].right_texture2.loadFromImage(image);
    player.hands[19].right2.setTexture(player.hands[19].right_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[19].right_texture3.loadFromImage(image);
    player.hands[19].right3.setTexture(player.hands[19].right_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[19].right_texture4.loadFromImage(image);
    player.hands[19].right4.setTexture(player.hands[19].right_texture4);
    image.loadFromFile("Textures/guns/pistol/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[19].left_texture1.loadFromImage(image);
    player.hands[19].left1.setTexture(player.hands[19].left_texture1);
    image.loadFromFile("Textures/guns/pistol/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[19].left_texture2.loadFromImage(image);
    player.hands[19].left2.setTexture(player.hands[19].left_texture2);
    image.loadFromFile("Textures/guns/pistol/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[19].left_texture3.loadFromImage(image);
    player.hands[19].left3.setTexture(player.hands[19].left_texture3);
    image.loadFromFile("Textures/guns/pistol/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[19].left_texture4.loadFromImage(image);
    player.hands[19].left4.setTexture(player.hands[19].left_texture4);

    image.loadFromFile("Textures/guns/machine_gun/right_hand1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[20].right_texture1.loadFromImage(image);
    player.hands[20].right1.setTexture(player.hands[20].right_texture1);
    image.loadFromFile("Textures/guns/machine_gun/right_hand2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[20].right_texture2.loadFromImage(image);
    player.hands[20].right2.setTexture(player.hands[20].right_texture2);
    image.loadFromFile("Textures/guns/machine_gun/right_hand3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[20].right_texture3.loadFromImage(image);
    player.hands[20].right3.setTexture(player.hands[20].right_texture3);
    image.loadFromFile("Textures/guns/machine_gun/right_hand4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[20].right_texture4.loadFromImage(image);
    player.hands[20].right4.setTexture(player.hands[20].right_texture4);
    image.loadFromFile("Textures/guns/goldenmg/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[20].left_texture1.loadFromImage(image);
    player.hands[20].left1.setTexture(player.hands[20].left_texture1);
    image.loadFromFile("Textures/guns/goldenmg/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[20].left_texture2.loadFromImage(image);
    player.hands[20].left2.setTexture(player.hands[20].left_texture2);
    image.loadFromFile("Textures/guns/goldenmg/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[20].left_texture3.loadFromImage(image);
    player.hands[20].left3.setTexture(player.hands[20].left_texture3);
    image.loadFromFile("Textures/guns/goldenmg/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[20].left_texture4.loadFromImage(image);
    player.hands[20].left4.setTexture(player.hands[20].left_texture4);

    image.loadFromFile("Textures/guns/shotgun/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[21].right_texture1.loadFromImage(image);
    player.hands[21].right1.setTexture(player.hands[21].right_texture1);
    image.loadFromFile("Textures/guns/shotgun/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[21].right_texture2.loadFromImage(image);
    player.hands[21].right2.setTexture(player.hands[21].right_texture2);
    image.loadFromFile("Textures/guns/shotgun/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[21].right_texture3.loadFromImage(image);
    player.hands[21].right3.setTexture(player.hands[21].right_texture3);
    image.loadFromFile("Textures/guns/shotgun/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[21].right_texture4.loadFromImage(image);
    player.hands[21].right4.setTexture(player.hands[21].right_texture4);
    image.loadFromFile("Textures/guns/goldenmg/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[21].left_texture1.loadFromImage(image);
    player.hands[21].left1.setTexture(player.hands[21].left_texture1);
    image.loadFromFile("Textures/guns/goldenmg/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[21].left_texture2.loadFromImage(image);
    player.hands[21].left2.setTexture(player.hands[21].left_texture2);
    image.loadFromFile("Textures/guns/goldenmg/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[21].left_texture3.loadFromImage(image);
    player.hands[21].left3.setTexture(player.hands[21].left_texture3);
    image.loadFromFile("Textures/guns/goldenmg/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[21].left_texture4.loadFromImage(image);
    player.hands[21].left4.setTexture(player.hands[21].left_texture4);

    image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[22].right_texture1.loadFromImage(image);
    player.hands[22].right1.setTexture(player.hands[22].right_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[22].right_texture2.loadFromImage(image);
    player.hands[22].right2.setTexture(player.hands[22].right_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[22].right_texture3.loadFromImage(image);
    player.hands[22].right3.setTexture(player.hands[22].right_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[22].right_texture4.loadFromImage(image);
    player.hands[22].right4.setTexture(player.hands[22].right_texture4);
    image.loadFromFile("Textures/guns/pistol/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[22].left_texture1.loadFromImage(image);
    player.hands[22].left1.setTexture(player.hands[22].left_texture1);
    image.loadFromFile("Textures/guns/pistol/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[22].left_texture2.loadFromImage(image);
    player.hands[22].left2.setTexture(player.hands[22].left_texture2);
    image.loadFromFile("Textures/guns/pistol/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[22].left_texture3.loadFromImage(image);
    player.hands[22].left3.setTexture(player.hands[22].left_texture3);
    image.loadFromFile("Textures/guns/pistol/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[22].left_texture4.loadFromImage(image);
    player.hands[22].left4.setTexture(player.hands[22].left_texture4);


    image.loadFromFile("Textures/guns/machine_gun/right_hand1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[23].right_texture1.loadFromImage(image);
    player.hands[23].right1.setTexture(player.hands[23].right_texture1);
    image.loadFromFile("Textures/guns/machine_gun/right_hand2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[23].right_texture2.loadFromImage(image);
    player.hands[23].right2.setTexture(player.hands[23].right_texture2);
    image.loadFromFile("Textures/guns/machine_gun/right_hand3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[23].right_texture3.loadFromImage(image);
    player.hands[23].right3.setTexture(player.hands[23].right_texture3);
    image.loadFromFile("Textures/guns/machine_gun/right_hand4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[23].right_texture4.loadFromImage(image);
    player.hands[23].right4.setTexture(player.hands[23].right_texture4);
    image.loadFromFile("Textures/guns/goldenmg/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[23].left_texture1.loadFromImage(image);
    player.hands[23].left1.setTexture(player.hands[23].left_texture1);
    image.loadFromFile("Textures/guns/goldenmg/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[23].left_texture2.loadFromImage(image);
    player.hands[23].left2.setTexture(player.hands[23].left_texture2);
    image.loadFromFile("Textures/guns/goldenmg/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[23].left_texture3.loadFromImage(image);
    player.hands[23].left3.setTexture(player.hands[23].left_texture3);
    image.loadFromFile("Textures/guns/goldenmg/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[23].left_texture4.loadFromImage(image);
    player.hands[23].left4.setTexture(player.hands[23].left_texture4);

    image.loadFromFile("Textures/guns/railgun/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[24].right_texture1.loadFromImage(image);
    player.hands[24].right1.setTexture(player.hands[24].right_texture1);
    image.loadFromFile("Textures/guns/railgun/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[24].right_texture2.loadFromImage(image);
    player.hands[24].right2.setTexture(player.hands[24].right_texture2);
    image.loadFromFile("Textures/guns/railgun/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[24].right_texture3.loadFromImage(image);
    player.hands[24].right3.setTexture(player.hands[24].right_texture3);
    image.loadFromFile("Textures/guns/railgun/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[24].right_texture4.loadFromImage(image);
    player.hands[24].right4.setTexture(player.hands[24].right_texture4);
    image.loadFromFile("Textures/guns/railgun/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[24].left_texture1.loadFromImage(image);
    player.hands[24].left1.setTexture(player.hands[24].left_texture1);
    image.loadFromFile("Textures/guns/railgun/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[24].left_texture2.loadFromImage(image);
    player.hands[24].left2.setTexture(player.hands[24].left_texture2);
    image.loadFromFile("Textures/guns/railgun/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[24].left_texture3.loadFromImage(image);
    player.hands[24].left3.setTexture(player.hands[24].left_texture3);
    image.loadFromFile("Textures/guns/railgun/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[24].left_texture4.loadFromImage(image);
    player.hands[24].left4.setTexture(player.hands[24].left_texture4);

    image.loadFromFile("Textures/guns/smg/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[25].right_texture1.loadFromImage(image);
    player.hands[25].right1.setTexture(player.hands[25].right_texture1);
    image.loadFromFile("Textures/guns/smg/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[25].right_texture2.loadFromImage(image);
    player.hands[25].right2.setTexture(player.hands[25].right_texture2);
    image.loadFromFile("Textures/guns/smg/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[25].right_texture3.loadFromImage(image);
    player.hands[25].right3.setTexture(player.hands[25].right_texture3);
    image.loadFromFile("Textures/guns/smg/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[25].right_texture4.loadFromImage(image);
    player.hands[25].right4.setTexture(player.hands[25].right_texture4);
    image.loadFromFile("Textures/guns/smg/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[25].left_texture1.loadFromImage(image);
    player.hands[25].left1.setTexture(player.hands[25].left_texture1);
    image.loadFromFile("Textures/guns/smg/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[25].left_texture2.loadFromImage(image);
    player.hands[25].left2.setTexture(player.hands[25].left_texture2);
    image.loadFromFile("Textures/guns/smg/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[25].left_texture3.loadFromImage(image);
    player.hands[25].left3.setTexture(player.hands[25].left_texture3);
    image.loadFromFile("Textures/guns/smg/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[25].left_texture4.loadFromImage(image);
    player.hands[25].left4.setTexture(player.hands[25].left_texture4);


    image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[26].right_texture1.loadFromImage(image);
    player.hands[26].right1.setTexture(player.hands[26].right_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[26].right_texture2.loadFromImage(image);
    player.hands[26].right2.setTexture(player.hands[26].right_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[26].right_texture3.loadFromImage(image);
    player.hands[26].right3.setTexture(player.hands[26].right_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[26].right_texture4.loadFromImage(image);
    player.hands[26].right4.setTexture(player.hands[26].right_texture4);
    image.loadFromFile("Textures/guns/pistol/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[26].left_texture1.loadFromImage(image);
    player.hands[26].left1.setTexture(player.hands[26].left_texture1);
    image.loadFromFile("Textures/guns/pistol/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[26].left_texture2.loadFromImage(image);
    player.hands[26].left2.setTexture(player.hands[26].left_texture2);
    image.loadFromFile("Textures/guns/pistol/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[26].left_texture3.loadFromImage(image);
    player.hands[26].left3.setTexture(player.hands[26].left_texture3);
    image.loadFromFile("Textures/guns/pistol/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[26].left_texture4.loadFromImage(image);
    player.hands[26].left4.setTexture(player.hands[26].left_texture4);


    image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[27].right_texture1.loadFromImage(image);
    player.hands[27].right1.setTexture(player.hands[27].right_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[27].right_texture2.loadFromImage(image);
    player.hands[27].right2.setTexture(player.hands[27].right_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[27].right_texture3.loadFromImage(image);
    player.hands[27].right3.setTexture(player.hands[27].right_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[27].right_texture4.loadFromImage(image);
    player.hands[27].right4.setTexture(player.hands[27].right_texture4);
    image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[27].left_texture1.loadFromImage(image);
    player.hands[27].left1.setTexture(player.hands[27].left_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[27].left_texture2.loadFromImage(image);
    player.hands[27].left2.setTexture(player.hands[27].left_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[27].left_texture3.loadFromImage(image);
    player.hands[27].left3.setTexture(player.hands[27].left_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[27].left_texture4.loadFromImage(image);
    player.hands[27].left4.setTexture(player.hands[27].left_texture4);

    image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[28].right_texture1.loadFromImage(image);
    player.hands[28].right1.setTexture(player.hands[28].right_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[28].right_texture2.loadFromImage(image);
    player.hands[28].right2.setTexture(player.hands[28].right_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[28].right_texture3.loadFromImage(image);
    player.hands[28].right3.setTexture(player.hands[28].right_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[28].right_texture4.loadFromImage(image);
    player.hands[28].right4.setTexture(player.hands[28].right_texture4);
    image.loadFromFile("Textures/guns/pistol/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[28].left_texture1.loadFromImage(image);
    player.hands[28].left1.setTexture(player.hands[28].left_texture1);
    image.loadFromFile("Textures/guns/pistol/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[28].left_texture2.loadFromImage(image);
    player.hands[28].left2.setTexture(player.hands[28].left_texture2);
    image.loadFromFile("Textures/guns/pistol/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[28].left_texture3.loadFromImage(image);
    player.hands[28].left3.setTexture(player.hands[28].left_texture3);
    image.loadFromFile("Textures/guns/pistol/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[28].left_texture4.loadFromImage(image);
    player.hands[28].left4.setTexture(player.hands[28].left_texture4);

    image.loadFromFile("Textures/guns/boosty&speedy/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[29].right_texture1.loadFromImage(image);
    player.hands[29].right1.setTexture(player.hands[29].right_texture1);
    image.loadFromFile("Textures/guns/boosty&speedy/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[29].right_texture2.loadFromImage(image);
    player.hands[29].right2.setTexture(player.hands[29].right_texture2);
    image.loadFromFile("Textures/guns/boosty&speedy/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[29].right_texture3.loadFromImage(image);
    player.hands[29].right3.setTexture(player.hands[29].right_texture3);
    image.loadFromFile("Textures/guns/boosty&speedy/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[29].right_texture4.loadFromImage(image);
    player.hands[29].right4.setTexture(player.hands[29].right_texture4);
    image.loadFromFile("Textures/guns/pistol/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[29].left_texture1.loadFromImage(image);
    player.hands[29].left1.setTexture(player.hands[29].left_texture1);
    image.loadFromFile("Textures/guns/pistol/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[29].left_texture2.loadFromImage(image);
    player.hands[29].left2.setTexture(player.hands[29].left_texture2);
    image.loadFromFile("Textures/guns/pistol/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[29].left_texture3.loadFromImage(image);
    player.hands[29].left3.setTexture(player.hands[29].left_texture3);
    image.loadFromFile("Textures/guns/pistol/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[29].left_texture4.loadFromImage(image);
    player.hands[29].left4.setTexture(player.hands[29].left_texture4);

    image.loadFromFile("Textures/guns/machine_gun/right_hand1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[30].right_texture1.loadFromImage(image);
    player.hands[30].right1.setTexture(player.hands[30].right_texture1);
    image.loadFromFile("Textures/guns/machine_gun/right_hand2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[30].right_texture2.loadFromImage(image);
    player.hands[30].right2.setTexture(player.hands[30].right_texture2);
    image.loadFromFile("Textures/guns/machine_gun/right_hand3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[30].right_texture3.loadFromImage(image);
    player.hands[30].right3.setTexture(player.hands[30].right_texture3);
    image.loadFromFile("Textures/guns/machine_gun/right_hand4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[30].right_texture4.loadFromImage(image);
    player.hands[30].right4.setTexture(player.hands[30].right_texture4);
    image.loadFromFile("Textures/guns/machine_gun/left_hand1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[30].left_texture1.loadFromImage(image);
    player.hands[30].left1.setTexture(player.hands[30].left_texture1);
    image.loadFromFile("Textures/guns/machine_gun/left_hand2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[30].left_texture2.loadFromImage(image);
    player.hands[30].left2.setTexture(player.hands[30].left_texture2);
    image.loadFromFile("Textures/guns/machine_gun/left_hand3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[30].left_texture3.loadFromImage(image);
    player.hands[30].left3.setTexture(player.hands[30].left_texture3);
    image.loadFromFile("Textures/guns/machine_gun/left_hand4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[30].left_texture4.loadFromImage(image);
    player.hands[30].left4.setTexture(player.hands[30].left_texture4);

    image.loadFromFile("Textures/guns/rocket_launcher/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[31].right_texture1.loadFromImage(image);
    player.hands[31].right1.setTexture(player.hands[31].right_texture1);
    image.loadFromFile("Textures/guns/rocket_launcher/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[31].right_texture2.loadFromImage(image);
    player.hands[31].right2.setTexture(player.hands[31].right_texture2);
    image.loadFromFile("Textures/guns/rocket_launcher/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[31].right_texture3.loadFromImage(image);
    player.hands[31].right3.setTexture(player.hands[31].right_texture3);
    image.loadFromFile("Textures/guns/rocket_launcher/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[31].right_texture4.loadFromImage(image);
    player.hands[31].right4.setTexture(player.hands[31].right_texture4);
    image.loadFromFile("Textures/guns/rocket_launcher/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[31].left_texture1.loadFromImage(image);
    player.hands[31].left1.setTexture(player.hands[31].left_texture1);
    image.loadFromFile("Textures/guns/rocket_launcher/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[31].left_texture2.loadFromImage(image);
    player.hands[31].left2.setTexture(player.hands[31].left_texture2);
    image.loadFromFile("Textures/guns/rocket_launcher/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[31].left_texture3.loadFromImage(image);
    player.hands[31].left3.setTexture(player.hands[31].left_texture3);
    image.loadFromFile("Textures/guns/rocket_launcher/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[31].left_texture4.loadFromImage(image);
    player.hands[31].left4.setTexture(player.hands[31].left_texture4);

    image.loadFromFile("Textures/guns/machine_gun/right_hand1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[32].right_texture1.loadFromImage(image);
    player.hands[32].right1.setTexture(player.hands[32].right_texture1);
    image.loadFromFile("Textures/guns/machine_gun/right_hand2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[32].right_texture2.loadFromImage(image);
    player.hands[32].right2.setTexture(player.hands[32].right_texture2);
    image.loadFromFile("Textures/guns/machine_gun/right_hand3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[32].right_texture3.loadFromImage(image);
    player.hands[32].right3.setTexture(player.hands[32].right_texture3);
    image.loadFromFile("Textures/guns/machine_gun/right_hand4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[32].right_texture4.loadFromImage(image);
    player.hands[32].right4.setTexture(player.hands[32].right_texture4);
    image.loadFromFile("Textures/guns/goldenmg/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[32].left_texture1.loadFromImage(image);
    player.hands[32].left1.setTexture(player.hands[32].left_texture1);
    image.loadFromFile("Textures/guns/goldenmg/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[32].left_texture2.loadFromImage(image);
    player.hands[32].left2.setTexture(player.hands[32].left_texture2);
    image.loadFromFile("Textures/guns/goldenmg/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[32].left_texture3.loadFromImage(image);
    player.hands[32].left3.setTexture(player.hands[32].left_texture3);
    image.loadFromFile("Textures/guns/goldenmg/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[32].left_texture4.loadFromImage(image);
    player.hands[32].left4.setTexture(player.hands[32].left_texture4);


    image.loadFromFile("Textures/guns/gatling/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[33].right_texture1.loadFromImage(image);
    player.hands[33].right1.setTexture(player.hands[33].right_texture1);
    image.loadFromFile("Textures/guns/gatling/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[33].right_texture2.loadFromImage(image);
    player.hands[33].right2.setTexture(player.hands[33].right_texture2);
    image.loadFromFile("Textures/guns/gatling/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[33].right_texture3.loadFromImage(image);
    player.hands[33].right3.setTexture(player.hands[33].right_texture3);
    image.loadFromFile("Textures/guns/gatling/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[33].right_texture4.loadFromImage(image);
    player.hands[33].right4.setTexture(player.hands[33].right_texture4);
    image.loadFromFile("Textures/guns/gatling/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[33].left_texture1.loadFromImage(image);
    player.hands[33].left1.setTexture(player.hands[33].left_texture1);
    image.loadFromFile("Textures/guns/gatling/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[33].left_texture2.loadFromImage(image);
    player.hands[33].left2.setTexture(player.hands[33].left_texture2);
    image.loadFromFile("Textures/guns/gatling/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[33].left_texture3.loadFromImage(image);
    player.hands[33].left3.setTexture(player.hands[33].left_texture3);
    image.loadFromFile("Textures/guns/gatling/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[33].left_texture4.loadFromImage(image);
    player.hands[33].left4.setTexture(player.hands[33].left_texture4);

    image.loadFromFile("Textures/guns/pistol/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[34].right_texture1.loadFromImage(image);
    player.hands[34].right1.setTexture(player.hands[34].right_texture1);
    image.loadFromFile("Textures/guns/pistol/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[34].right_texture2.loadFromImage(image);
    player.hands[34].right2.setTexture(player.hands[34].right_texture2);
    image.loadFromFile("Textures/guns/pistol/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[34].right_texture3.loadFromImage(image);
    player.hands[34].right3.setTexture(player.hands[34].right_texture3);
    image.loadFromFile("Textures/guns/pistol/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[34].right_texture4.loadFromImage(image);
    player.hands[34].right4.setTexture(player.hands[34].right_texture4);
    image.loadFromFile("Textures/guns/knife/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[34].left_texture1.loadFromImage(image);
    player.hands[34].left1.setTexture(player.hands[34].left_texture1);
    image.loadFromFile("Textures/guns/knife/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[34].left_texture2.loadFromImage(image);
    player.hands[34].left2.setTexture(player.hands[34].left_texture2);
    image.loadFromFile("Textures/guns/knife/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[34].left_texture3.loadFromImage(image);
    player.hands[34].left3.setTexture(player.hands[34].left_texture3);
    image.loadFromFile("Textures/guns/knife/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[34].left_texture4.loadFromImage(image);
    player.hands[34].left4.setTexture(player.hands[34].left_texture4);

    image.loadFromFile("Textures/guns/skeleton/right1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[35].right_texture1.loadFromImage(image);
    player.hands[35].right1.setTexture(player.hands[35].right_texture1);
    image.loadFromFile("Textures/guns/skeleton/right2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[35].right_texture2.loadFromImage(image);
    player.hands[35].right2.setTexture(player.hands[35].right_texture2);
    image.loadFromFile("Textures/guns/skeleton/right3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[35].right_texture3.loadFromImage(image);
    player.hands[35].right3.setTexture(player.hands[35].right_texture3);
    image.loadFromFile("Textures/guns/skeleton/right4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[35].right_texture4.loadFromImage(image);
    player.hands[35].right4.setTexture(player.hands[35].right_texture4);
    image.loadFromFile("Textures/guns/skeleton/left1.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[35].left_texture1.loadFromImage(image);
    player.hands[35].left1.setTexture(player.hands[35].left_texture1);
    image.loadFromFile("Textures/guns/skeleton/left2.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[35].left_texture2.loadFromImage(image);
    player.hands[35].left2.setTexture(player.hands[35].left_texture2);
    image.loadFromFile("Textures/guns/skeleton/left3.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[35].left_texture3.loadFromImage(image);
    player.hands[35].left3.setTexture(player.hands[35].left_texture3);
    image.loadFromFile("Textures/guns/skeleton/left4.png");
    image.createMaskFromColor(Color(255, 255, 255));
    player.hands[35].left_texture4.loadFromImage(image);
    player.hands[35].left4.setTexture(player.hands[35].left_texture4);*/

    for (int i=0; i<guns_count; i++)
    {
        guns[i].temp+=guns[i].name;
        guns[i].temp+="\n";
        guns[i].temp+="Damage: ";
        guns[i].temp+=std::to_string(guns[i].damage);
        guns[i].temp+="*";
        guns[i].temp+=std::to_string(guns[i].pellets*2+1);
        guns[i].temp+="\n";
        guns[i].temp+="Fire Rate: ";
        if (guns[i].ammo_used<guns[i].max_ammo)
        {
            guns[i].temp+=std::to_string(60/double(guns[i].max_delay));
        }
        else
        {
            guns[i].temp+=std::to_string(60/double(guns[i].max_reload));
        }
        guns[i].temp+="\n";
        guns[i].temp+="Capacity: ";
        guns[i].temp+=std::to_string(guns[i].max_ammo);
        guns[i].temp+="\n";
        guns[i].temp+="Swiftness: ";
        guns[i].temp+=std::to_string(guns[i].swiftness);

        //guns[i].stats.setString(guns[i].temp);
    }

    for (int i=0; i<enemy[4][0].quantity; i++)
    {
        enemy[4][i].max_health=2880;
        enemy[4][i].gun_holding=11;
        enemy[4][i].max_delay=110;
        enemy[4][i].max_guns_delay=1;

        enemy[4][i].body.create(6, 100, 100, 50, 0, 1);
            enemy[4][i].body.fill_frames("Textures/shotgunner/", 1);

            enemy[4][i].left.create(2, 100, 100, 50, 50, 0.1);
            enemy[4][i].left.fill_frames("Textures/shotgunner/left", 1);
            enemy[4][i].left.f_count=guns[11].left.f_count;
            enemy[4][i].left.frame_pos=guns[11].left.frame_pos;

            enemy[4][i].right.create(2, 100, 100, 50, 50, 0.1);
            enemy[4][i].right.fill_frames("Textures/shotgunner/right", 1);
            enemy[4][i].right.f_count=guns[11].right.f_count;
            enemy[4][i].right.frame_pos=guns[11].right.frame_pos;


            enemy[4][i].left_reload.create(1, 100, 100, 50, 50, 0.1);
            enemy[4][i].left_reload.fill_frames("Textures/shotgunner/left", 1);
            enemy[4][i].left_reload.f_count=guns[11].left_reload.f_count;
            enemy[4][i].left_reload.frame_pos=guns[11].left_reload.frame_pos;

            enemy[4][i].right_reload.create(5, 100, 100, 50, 50, 0.1);
            enemy[4][i].right_reload.fill_frames("Textures/shotgunner/right_reload", 1);
            enemy[4][i].right_reload.f_count=guns[11].right_reload.f_count;
            enemy[4][i].right_reload.frame_pos=guns[11].right_reload.frame_pos;

            enemy[4][i].head.create(1, 50, 50, 25, 50, 1);
            enemy[4][i].head.fill_frames("Textures/shotgunner/head", 1);
            //enemy[0][i].gun_holding=1;


            enemy[4][i].weapon_buffer=guns[11].buffer;
            enemy[4][i].weapon_sound.setBuffer(enemy[4][i].weapon_buffer);

            enemy[4][i].reload_sound.setBuffer(guns[11].reload_buffer);

            enemy[4][i].bullet_texture=guns[11].bullet_texture;
            enemy[4][i].bullet.setTexture(enemy[4][i].bullet_texture);
            enemy[4][i].bullet.setTextureRect(IntRect(0, 0, 1, 2));

            enemy[4][i].idle.loadFromFile("Textures/shotgunner/idle.png");
            enemy[4][i].jump.loadFromFile("Textures/shotgunner/jump.png");


        /*enemy[4][i].hands[enemy[4][i].gun_holding].left1.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[4][i].hands[enemy[4][i].gun_holding].left2.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[4][i].hands[enemy[4][i].gun_holding].left3.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[4][i].hands[enemy[4][i].gun_holding].left4.setTextureRect(IntRect(0, 0, 50, 50));*/

        /*enemy[4][i].hands[enemy[4][i].gun_holding].right1.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[4][i].hands[enemy[4][i].gun_holding].right2.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[4][i].hands[enemy[4][i].gun_holding].right3.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[4][i].hands[enemy[4][i].gun_holding].right4.setTextureRect(IntRect(0, 0, 50, 50));*/

        //enemy[4][i].body4.setRotation(90);

        /*image.loadFromFile("Textures/shotgunner/body1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[4][i].body_texture1.loadFromImage(image);
        enemy[4][i].body1.setTexture(enemy[4][i].body_texture1);
        image.loadFromFile("Textures/shotgunner/body4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[4][i].body_texture4.loadFromImage(image);
        enemy[4][i].body4.setTexture(enemy[4][i].body_texture4);

        image.loadFromFile("Textures/shotgunner/head2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[4][i].head_texture2.loadFromImage(image);
        enemy[4][i].head2.setTexture(enemy[4][i].head_texture2);
        image.loadFromFile("Textures/shotgunner/head3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[4][i].head_texture3.loadFromImage(image);
        enemy[4][i].head3.setTexture(enemy[4][i].head_texture3);

        image.loadFromFile("Textures/shotgunner/right1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[4][i].hands[11].right_texture1.loadFromImage(image);
        enemy[4][i].hands[11].right1.setTexture(enemy[4][i].hands[11].right_texture1);
        image.loadFromFile("Textures/shotgunner/right2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[4][i].hands[11].right_texture2.loadFromImage(image);
        enemy[4][i].hands[11].right2.setTexture(enemy[4][i].hands[11].right_texture2);
        image.loadFromFile("Textures/shotgunner/right3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[4][i].hands[11].right_texture3.loadFromImage(image);
        enemy[4][i].hands[11].right3.setTexture(enemy[4][i].hands[11].right_texture3);
        image.loadFromFile("Textures/shotgunner/right4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[4][i].hands[11].right_texture4.loadFromImage(image);
        enemy[4][i].hands[11].right4.setTexture(enemy[4][i].hands[11].right_texture4);

        image.loadFromFile("Textures/shotgunner/left1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[4][i].hands[11].left_texture1.loadFromImage(image);
        enemy[4][i].hands[11].left1.setTexture(enemy[4][i].hands[11].left_texture1);
        image.loadFromFile("Textures/shotgunner/left2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[4][i].hands[11].left_texture2.loadFromImage(image);
        enemy[4][i].hands[11].left2.setTexture(enemy[4][i].hands[11].left_texture2);
        image.loadFromFile("Textures/shotgunner/left3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[4][i].hands[11].left_texture3.loadFromImage(image);
        enemy[4][i].hands[11].left3.setTexture(enemy[4][i].hands[11].left_texture3);
        image.loadFromFile("Textures/shotgunner/left4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[4][i].hands[11].left_texture4.loadFromImage(image);
        enemy[4][i].hands[11].left4.setTexture(enemy[4][i].hands[11].left_texture4);

        image.loadFromFile("Textures/bullet.png");
        enemy[4][i].bullet_texture.loadFromImage(image);
        enemy[4][i].bullet.setTexture(enemy[4][i].bullet_texture);

        enemy[4][i].weapon_buffer.loadFromFile("Sounds/guns/double/sound.wav");
        enemy[4][i].weapon_sound.setBuffer(enemy[4][i].weapon_buffer);*/
    }
    for (int i=0; i<enemy[3][0].quantity; i++)
    {

        enemy[3][i].gun_holding=3;
        enemy[3][i].max_delay=40;
        enemy[3][i].max_health=144;

        enemy[3][i].body.create(6, 100, 100, 50, 0, 1);
            enemy[3][i].body.fill_frames("Textures/marksman/", 1);

            enemy[3][i].left.create(3, 100, 100, 50, 50, 0.1);
            enemy[3][i].left.fill_frames("Textures/marksman/left", 1);
            enemy[3][i].left.f_count=guns[3].left.f_count;
            enemy[3][i].left.frame_pos=guns[3].left.frame_pos;

            enemy[3][i].right.create(2, 100, 100, 50, 50, 0.1);
            enemy[3][i].right.fill_frames("Textures/marksman/right", 1);
            enemy[3][i].right.f_count=guns[3].right.f_count;
            enemy[3][i].right.frame_pos=guns[3].right.frame_pos;

            enemy[3][i].head.create(2, 50, 50, 25, 50, 1);
            enemy[3][i].head.fill_frames("Textures/marksman/head", 1);
            //enemy[0][i].gun_holding=1;


            enemy[3][i].weapon_buffer=guns[3].buffer;
            enemy[3][i].weapon_sound.setBuffer(enemy[3][i].weapon_buffer);

            enemy[3][i].bullet_texture=guns[3].bullet_texture;
            enemy[3][i].bullet.setTexture(enemy[3][i].bullet_texture);
            enemy[3][i].bullet.setTextureRect(IntRect(0, 0, 1, 2));

            enemy[3][i].idle.loadFromFile("Textures/marksman/idle.png");
            enemy[3][i].jump.loadFromFile("Textures/marksman/jump.png");

        /*enemy[3][i].hands[enemy[3][i].gun_holding].left1.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[3][i].hands[enemy[3][i].gun_holding].left2.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[3][i].hands[enemy[3][i].gun_holding].left3.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[3][i].hands[enemy[3][i].gun_holding].left4.setTextureRect(IntRect(0, 0, 50, 50));

        enemy[3][i].hands[enemy[3][i].gun_holding].right1.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[3][i].hands[enemy[3][i].gun_holding].right2.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[3][i].hands[enemy[3][i].gun_holding].right3.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[3][i].hands[enemy[3][i].gun_holding].right4.setTextureRect(IntRect(0, 0, 50, 50));*/

        /*enemy[3][i].body4.setRotation(90);

        image.loadFromFile("Textures/enemy/body1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[3][i].body_texture1.loadFromImage(image);
        enemy[3][i].body1.setTexture(enemy[3][i].body_texture1);
        image.loadFromFile("Textures/enemy/body4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[3][i].body_texture4.loadFromImage(image);
        enemy[3][i].body4.setTexture(enemy[3][i].body_texture4);

        image.loadFromFile("Textures/enemy/head2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[3][i].head_texture2.loadFromImage(image);
        enemy[3][i].head2.setTexture(enemy[3][i].head_texture2);
        image.loadFromFile("Textures/enemy/head3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[3][i].head_texture3.loadFromImage(image);
        enemy[3][i].head3.setTexture(enemy[3][i].head_texture3);

        image.loadFromFile("Textures/marksman/right1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[3][i].hands[3].right_texture1.loadFromImage(image);
        enemy[3][i].hands[3].right1.setTexture(enemy[3][i].hands[3].right_texture1);
        image.loadFromFile("Textures/marksman/right2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[3][i].hands[3].right_texture2.loadFromImage(image);
        enemy[3][i].hands[3].right2.setTexture(enemy[3][i].hands[3].right_texture2);
        image.loadFromFile("Textures/marksman/right3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[3][i].hands[3].right_texture3.loadFromImage(image);
        enemy[3][i].hands[3].right3.setTexture(enemy[3][i].hands[3].right_texture3);
        image.loadFromFile("Textures/marksman/right4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[3][i].hands[3].right_texture4.loadFromImage(image);
        enemy[3][i].hands[3].right4.setTexture(enemy[3][i].hands[3].right_texture4);

        image.loadFromFile("Textures/marksman/left1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[3][i].hands[3].left_texture1.loadFromImage(image);
        enemy[3][i].hands[3].left1.setTexture(enemy[3][i].hands[3].left_texture1);
        image.loadFromFile("Textures/marksman/left2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[3][i].hands[3].left_texture2.loadFromImage(image);
        enemy[3][i].hands[3].left2.setTexture(enemy[3][i].hands[3].left_texture2);
        image.loadFromFile("Textures/marksman/left3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[3][i].hands[3].left_texture3.loadFromImage(image);
        enemy[3][i].hands[3].left3.setTexture(enemy[3][i].hands[3].left_texture3);
        image.loadFromFile("Textures/marksman/left4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[3][i].hands[3].left_texture4.loadFromImage(image);
        enemy[3][i].hands[3].left4.setTexture(enemy[3][i].hands[3].left_texture4);

        enemy[3][i].weapon_buffer.loadFromFile("Sounds/guns/lever_action/lever_sound.wav");
        enemy[3][i].weapon_sound.setBuffer(enemy[3][i].weapon_buffer);

        image.loadFromFile("Textures/bullet.png");
        enemy[3][i].bullet_texture.loadFromImage(image);
        enemy[3][i].bullet.setTexture(enemy[3][i].bullet_texture);*/
    }
    for (int i=0; i<enemy[2][0].quantity; i++)
    {

        enemy[2][i].max_guns_delay=12;
        enemy[2][i].gun_holding=0;
        enemy[2][i].max_health=600;
        enemy[2][i].weapon_buffer.loadFromFile("Sounds/guns/0/0.wav");
        enemy[2][i].weapon_sound.setBuffer(enemy[2][i].weapon_buffer);

        enemy[2][i].bullet_texture=guns[0].bullet_texture;
        enemy[2][i].bullet.setTexture(enemy[2][i].bullet_texture);
            enemy[2][i].bullet.setTextureRect(IntRect(0, 0, 1, 2));

            enemy[2][i].idle.loadFromFile("Textures/machine_gunner/idle.png");
            enemy[2][i].jump.loadFromFile("Textures/machine_gunner/jump.png");

        enemy[2][i].left.create(2, 100, 100, 50, 50, 0.1);
        enemy[2][i].left.fill_frames("Textures/machine_gunner/left", 1);
        enemy[2][i].left.frame_pos=guns[0].left.frame_pos;
        enemy[2][i].left.f_count=guns[0].left.f_count;

        enemy[2][i].right.create(2, 100, 100, 50, 50, 0.1);
        enemy[2][i].right.fill_frames("Textures/machine_gunner/right", 1);
        enemy[2][i].right.frame_pos=guns[0].right.frame_pos;
        enemy[2][i].right.f_count=guns[0].right.f_count;


        enemy[2][i].body.create(6, 100, 100, 50, 0, 1);
        enemy[2][i].body.fill_frames("Textures/machine_gunner/", 1);


        enemy[2][i].head.create(1, 50, 50, 25, 50, 0.1);
        enemy[2][i].head.fill_frames("Textures/machine_gunner/head", 1);

        //enemy[2][i].gun_holding=0;







        /*enemy[2][i].hands[enemy[2][i].gun_holding].left1.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[2][i].hands[enemy[2][i].gun_holding].left2.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[2][i].hands[enemy[2][i].gun_holding].left3.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[2][i].hands[enemy[2][i].gun_holding].left4.setTextureRect(IntRect(0, 0, 50, 50));

        enemy[2][i].hands[enemy[2][i].gun_holding].right1.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[2][i].hands[enemy[2][i].gun_holding].right2.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[2][i].hands[enemy[2][i].gun_holding].right3.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[2][i].hands[enemy[2][i].gun_holding].right4.setTextureRect(IntRect(0, 0, 50, 50));*/

        /*enemy[2][i].body4.setRotation(90);

        image.loadFromFile("Textures/machine_gunner/body1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[2][i].body_texture1.loadFromImage(image);
        enemy[2][i].body1.setTexture(enemy[2][i].body_texture1);
        image.loadFromFile("Textures/machine_gunner/body4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[2][i].body_texture4.loadFromImage(image);
        enemy[2][i].body4.setTexture(enemy[2][i].body_texture4);

        image.loadFromFile("Textures/machine_gunner/head2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[2][i].head_texture2.loadFromImage(image);
        enemy[2][i].head2.setTexture(enemy[2][i].head_texture2);
        image.loadFromFile("Textures/machine_gunner/head3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[2][i].head_texture3.loadFromImage(image);
        enemy[2][i].head3.setTexture(enemy[2][i].head_texture3);

        image.loadFromFile("Textures/machine_gunner/right1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[2][i].hands[0].right_texture1.loadFromImage(image);
        enemy[2][i].hands[0].right1.setTexture(enemy[2][i].hands[0].right_texture1);
        image.loadFromFile("Textures/machine_gunner/right2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[2][i].hands[0].right_texture2.loadFromImage(image);
        enemy[2][i].hands[0].right2.setTexture(enemy[2][i].hands[0].right_texture2);
        image.loadFromFile("Textures/machine_gunner/right3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[2][i].hands[0].right_texture3.loadFromImage(image);
        enemy[2][i].hands[0].right3.setTexture(enemy[2][i].hands[0].right_texture3);
        image.loadFromFile("Textures/machine_gunner/right4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[2][i].hands[0].right_texture4.loadFromImage(image);
        enemy[2][i].hands[0].right4.setTexture(enemy[2][i].hands[0].right_texture4);

        image.loadFromFile("Textures/machine_gunner/left1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[2][i].hands[0].left_texture1.loadFromImage(image);
        enemy[2][i].hands[0].left1.setTexture(enemy[2][i].hands[0].left_texture1);
        image.loadFromFile("Textures/machine_gunner/left2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[2][i].hands[0].left_texture2.loadFromImage(image);
        enemy[2][i].hands[0].left2.setTexture(enemy[2][i].hands[0].left_texture2);
        image.loadFromFile("Textures/machine_gunner/left3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[2][i].hands[0].left_texture3.loadFromImage(image);
        enemy[2][i].hands[0].left3.setTexture(enemy[2][i].hands[0].left_texture3);
        image.loadFromFile("Textures/machine_gunner/left4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[2][i].hands[0].left_texture4.loadFromImage(image);
        enemy[2][i].hands[0].left4.setTexture(enemy[2][i].hands[0].left_texture4);

        image.loadFromFile("Textures/bullet.png");
        enemy[2][i].bullet_texture.loadFromImage(image);
        enemy[2][i].bullet.setTexture(enemy[2][i].bullet_texture);*/


        }
        for (int i=0; i<enemy[1][0].quantity; i++)
        {
            enemy[1][i].body.create(1, 200, 200, 100, 100, 1);
            enemy[1][i].body.fill_frames("Textures/dummy/", 1);

            enemy[1][i].head.create(1, 100, 100, 50, 50, 1);
            enemy[1][i].head.fill_frames("Textures/dummy/head", 1);
            enemy[1][i].max_health=120;

        /*image.loadFromFile("Textures/dummy/body1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[1][i].body_texture1.loadFromImage(image);
        enemy[1][i].body1.setTexture(enemy[1][i].body_texture1);
        image.loadFromFile("Textures/dummy/body4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[1][i].body_texture4.loadFromImage(image);
        enemy[1][i].body4.setTexture(enemy[1][i].body_texture4);

        image.loadFromFile("Textures/dummy/head2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[1][i].head_texture2.loadFromImage(image);
        enemy[1][i].head2.setTexture(enemy[1][i].head_texture2);
        image.loadFromFile("Textures/dummy/head3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[1][i].head_texture3.loadFromImage(image);
        enemy[1][i].head3.setTexture(enemy[1][i].head_texture3);

        enemy[1][i].body1.setTextureRect(IntRect(0, 0, 100, 100));
        enemy[1][i].body4.setTextureRect(IntRect(0, 0, 100, 100));

        enemy[1][i].body1.setScale(-1, 1);
        enemy[1][i].body4.setScale(1, -1);
        enemy[1][i].head2.setScale(1, -1);
        enemy[1][i].head3.setScale(-1, 1);
        enemy[1][i].body4.setRotation(90);
        enemy[1][i].head2.setRotation(270);
        enemy[1][i].head3.setRotation(180);*/
        }
        for (int i=0; i<enemy[0][0].quantity; i++)
        {
            enemy[0][i].max_health=120;
            enemy[0][i].body.create(6, 100, 100, 50, 0, 1);
            enemy[0][i].body.fill_frames("Textures/enemy/", 1);

            enemy[0][i].left.create(2, 100, 100, 50, 50, 0.1);
            enemy[0][i].left.fill_frames("Textures/enemy/left", 1);
            enemy[0][i].left.f_count=guns[1].left.f_count;
            enemy[0][i].left.frame_pos=guns[1].left.frame_pos;

            enemy[0][i].right.create(1, 100, 100, 50, 50, 0.1);
            enemy[0][i].right.fill_frames("Textures/enemy/right", 1);
            enemy[0][i].right.f_count=guns[1].right.f_count;
            enemy[0][i].right.frame_pos=guns[1].right.frame_pos;

            enemy[0][i].head.create(2, 50, 50, 25, 50, 1);
            enemy[0][i].head.fill_frames("Textures/enemy/head", 1);
            enemy[0][i].gun_holding=1;


            enemy[0][i].weapon_buffer=guns[1].buffer;
            enemy[0][i].weapon_sound.setBuffer(enemy[0][i].weapon_buffer);

            enemy[0][i].bullet_texture=guns[1].bullet_texture;
            enemy[0][i].bullet.setTexture(enemy[0][i].bullet_texture);
            enemy[0][i].bullet.setTextureRect(IntRect(0, 0, 1, 2));

            enemy[0][i].idle.loadFromFile("Textures/enemy/idle.png");
            enemy[0][i].jump.loadFromFile("Textures/enemy/jump.png");

        /*
        image.loadFromFile("Textures/enemy/body1.png");
        image.createMaskFromColor(Color(255, 255, 255));//body4
        enemy[0][i].body_texture1.loadFromImage(image);
        enemy[0][i].body1.setTexture(enemy[0][i].body_texture1);
        image.loadFromFile("Textures/enemy/body4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].body_texture4.loadFromImage(image);
        enemy[0][i].body4.setTexture(enemy[0][i].body_texture4);

        image.loadFromFile("Textures/enemy/head2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].head_texture2.loadFromImage(image);
        enemy[0][i].head2.setTexture(enemy[0][i].head_texture2);
        image.loadFromFile("Textures/enemy/head3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].head_texture3.loadFromImage(image);
        enemy[0][i].head3.setTexture(enemy[0][i].head_texture3);





        enemy[0][i].weapon_buffer.loadFromFile("Sounds/guns/pistol/pistol_sound.wav");
        enemy[0][i].weapon_sound.setBuffer(enemy[0][i].weapon_buffer);

        /*enemy[0][i].hands[enemy[0][i].gun_holding].left1.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[0][i].hands[enemy[0][i].gun_holding].left2.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[0][i].hands[enemy[0][i].gun_holding].left3.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[0][i].hands[enemy[0][i].gun_holding].left4.setTextureRect(IntRect(0, 0, 50, 50));

        enemy[0][i].hands[enemy[0][i].gun_holding].right1.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[0][i].hands[enemy[0][i].gun_holding].right2.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[0][i].hands[enemy[0][i].gun_holding].right3.setTextureRect(IntRect(0, 0, 50, 50));
        enemy[0][i].hands[enemy[0][i].gun_holding].right4.setTextureRect(IntRect(0, 0, 50, 50));*/

        //enemy[0][i].body4.setRotation(90);
//String
        /*image.loadFromFile("Textures/enemy/body1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].body_texture1.loadFromImage(image);
        enemy[0][i].body1.setTexture(enemy[0][i].body_texture1);
        image.loadFromFile("Textures/enemy/body4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].body_texture4.loadFromImage(image);
        enemy[0][i].body4.setTexture(enemy[0][i].body_texture4);

        image.loadFromFile("Textures/enemy/head2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].head_texture2.loadFromImage(image);
        enemy[0][i].head2.setTexture(enemy[0][i].head_texture2);
        image.loadFromFile("Textures/enemy/head3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].head_texture3.loadFromImage(image);
        enemy[0][i].head3.setTexture(enemy[0][i].head_texture3);

        image.loadFromFile("Textures/enemy/right1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].hands[1].right_texture1.loadFromImage(image);
        enemy[0][i].hands[1].right1.setTexture(enemy[0][i].hands[1].right_texture1);
        image.loadFromFile("Textures/enemy/right2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].hands[1].right_texture2.loadFromImage(image);
        enemy[0][i].hands[1].right2.setTexture(enemy[0][i].hands[1].right_texture2);
        image.loadFromFile("Textures/enemy/right3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].hands[1].right_texture3.loadFromImage(image);
        enemy[0][i].hands[1].right3.setTexture(enemy[0][i].hands[1].right_texture3);
        image.loadFromFile("Textures/enemy/right4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].hands[1].right_texture4.loadFromImage(image);
        enemy[0][i].hands[1].right4.setTexture(enemy[0][i].hands[1].right_texture4);

        image.loadFromFile("Textures/enemy/left1.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].hands[1].left_texture1.loadFromImage(image);
        enemy[0][i].hands[1].left1.setTexture(enemy[0][i].hands[1].left_texture1);
        image.loadFromFile("Textures/enemy/left2.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].hands[1].left_texture2.loadFromImage(image);
        enemy[0][i].hands[1].left2.setTexture(enemy[0][i].hands[1].left_texture2);
        image.loadFromFile("Textures/enemy/left3.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].hands[1].left_texture3.loadFromImage(image);
        enemy[0][i].hands[1].left3.setTexture(enemy[0][i].hands[1].left_texture3);
        image.loadFromFile("Textures/enemy/left4.png");
        image.createMaskFromColor(Color(255, 255, 255));
        enemy[0][i].hands[1].left_texture4.loadFromImage(image);
        enemy[0][i].hands[1].left4.setTexture(enemy[0][i].hands[1].left_texture4);

        image.loadFromFile("Textures/bullet.png");
        enemy[0][i].bullet_texture.loadFromImage(image);
        enemy[0][i].bullet.setTexture(enemy[0][i].bullet_texture);*/
    }

    for (int k=0; k<max_waves; k++)
    {
        for (int i=0; i<types; i++)
        {
            for (int j=0; j<enemy[i][0].quantity; j++)
            {

                waves[k].position[i][j]=enemy[i][j].position;
                waves[k].health[i][j]=0;


            }
        }
    }

    waves[0].health[0][0]=enemy[0][0].max_health;
    waves[0].position[0][0].pos.x=2800;
    waves[0].position[0][0].pos.y=3200;
    waves[0].position[0][0].speed.x=0;
    waves[0].position[0][0].speed.y=0;

    waves[0].health[0][1]=enemy[0][1].max_health;
    waves[0].position[0][1].pos.x=4880;
    waves[0].position[0][1].pos.y=3200;
    waves[0].position[0][1].speed.x=0;
    waves[0].position[0][1].speed.y=0;

    waves[0].health[0][2]=enemy[0][2].max_health;
    waves[0].position[0][2].pos.x=3840;
    waves[0].position[0][2].pos.y=3200;
    waves[0].position[0][2].speed.x=0;
    waves[0].position[0][2].speed.y=0;

    waves[1].health[0][0]=enemy[0][0].max_health;
    waves[1].position[0][0].pos.x=1800;
    waves[1].position[0][0].pos.y=3200;
    waves[1].position[0][0].speed.x=0;
    waves[1].position[0][0].speed.y=0;

    waves[1].health[0][1]=enemy[0][1].max_health;
    waves[1].position[0][1].pos.x=5880;
    waves[1].position[0][1].pos.y=3200;
    waves[1].position[0][1].speed.x=0;
    waves[1].position[0][1].speed.y=0;

    waves[1].health[0][2]=enemy[0][2].max_health;
    waves[1].position[0][2].pos.x=2800;
    waves[1].position[0][2].pos.y=3200;
    waves[1].position[0][2].speed.x=0;
    waves[1].position[0][2].speed.y=0;

    waves[1].health[0][3]=enemy[0][3].max_health;
    waves[1].position[0][3].pos.x=4880;
    waves[1].position[0][3].pos.y=3200;
    waves[1].position[0][3].speed.x=0;
    waves[1].position[0][3].speed.y=0;

    waves[1].health[0][4]=enemy[0][4].max_health;
    waves[1].position[0][4].pos.x=3840;
    waves[1].position[0][4].pos.y=3200;
    waves[1].position[0][4].speed.x=0;
    waves[1].position[0][4].speed.y=0;


    waves[2].health[2][0]=enemy[2][0].max_health;
    waves[2].position[2][0].pos.x=3840;
    waves[2].position[2][0].pos.y=3200;
    waves[2].position[2][0].speed.x=0;
    waves[2].position[2][0].speed.y=0;

    //player.body1.setPosition(960, 540);
    //player.body4.setPosition(960, 540);
    //player.head2.setPosition(960, 540);
    //player.head3.setPosition(960, 540);
    /*for (int i=0; i<guns_count; i++)
    {
        player.hands[i].right1.setPosition(960, 540);
        player.hands[i].right2.setPosition(960, 540);
        player.hands[i].right3.setPosition(960, 540);
        player.hands[i].right4.setPosition(960, 540);

        player.hands[i].left1.setPosition(960, 540);
        player.hands[i].left2.setPosition(960, 540);
        player.hands[i].left3.setPosition(960, 540);
        player.hands[i].left4.setPosition(960, 540);
    }*/


    player.max_health=144;

    //player.body4.setRotation(90);

    enemy_player=player;



    Clock clock;

    char type='a';
    IpAddress ip;

    TcpListener listener;



    Packet packet;



    TcpSocket socket;


    //std::cout << cos(rotation(0, -1));
    RenderWindow window(VideoMode(1920, 1080), "Guns", Style::Fullscreen);

    /*double multiplier;
    if (double(double(VideoMode::getDesktopMode().width)/double(VideoMode(1280, 720).width))<double(double(VideoMode::getDesktopMode().height)/double(VideoMode(1280, 720).height)))
    {
        multiplier=double(double(VideoMode::getDesktopMode().width)/double(VideoMode(1280, 720).width));
    }
    else
    {
        multiplier=double(double(VideoMode::getDesktopMode().height)/double(VideoMode(1280, 720).height));
    }*/

    window.setSize(Vector2u(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));

    //std::cout << VideoMode::getDesktopMode().width;mp
    window.setMouseCursorVisible(false);


    while (window.isOpen())
    {
        hitstate=0;


        /*player.hands[player.gun_holding].left1.setPosition(960, 540);
        player.hands[player.gun_holding].left2.setPosition(960, 540);
        player.hands[player.gun_holding].left3.setPosition(960, 540);
        player.hands[player.gun_holding].left4.setPosition(960, 540);

        player.hands[player.gun_holding].right1.setPosition(960, 540);
        player.hands[player.gun_holding].right2.setPosition(960, 540);
        player.hands[player.gun_holding].right3.setPosition(960, 540);
        player.hands[player.gun_holding].right4.setPosition(960, 540);*/

        Bullet subbullet;
        Bullet bullet;
        int ty=0;
        int nb=0;
        int dist=99999;
        window.clear();
        while (clock.getElapsedTime().asMicroseconds()<16667){}
        clock.restart();

        Vector2i pos=Mouse::getPosition(window);
        //int pos_x=round1(pos.x*multiplier);
        //int pos_y=round1(pos.y*multiplier);
        //pos=Vector2i(pos_x, pos_y);
        //Vector2f pos=window.mapPixelToCoords(mousepos);
        //pos=pos;
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type==Event::MouseWheelMoved)
{
    player.deploy=guns[player.gun_holding].max_deploy;
        guns[player.gun_holding].reload_sound.stop();
        guns[player.gun_holding].sound.stop();
    if (event.mouseWheel.delta<0)
    {
        if (player.gun_holding==primary)
        {
            player.gun_holding=secondary;
        }
        else if (player.gun_holding==secondary)
        {
            player.gun_holding=special;
        }
        else if (player.gun_holding==special)
        {
            player.gun_holding=primary;
        }
        player.deploy=guns[player.gun_holding].max_deploy;
    }
    else if (event.mouseWheel.delta>0)
    {

        if (player.gun_holding==primary)
        {
            player.gun_holding=special;
        }
        else if (player.gun_holding==secondary)
        {
            player.gun_holding=primary;
        }
        else if (player.gun_holding==special)
        {
            player.gun_holding=secondary;
        }

    }
}

//
            if (event.type == Event::Closed)
                window.close();
        }
        if (wasF11Pressed&&!Keyboard::isKeyPressed(Keyboard::F11))
            isF11Released=true;
        else
            isF11Released=false;
        if (Keyboard::isKeyPressed(Keyboard::F11))
            wasF11Pressed=true;
        else
            wasF11Pressed=false;

        if (wasPressed&&!Mouse::isButtonPressed(Mouse::Left))
            isReleased=true;
        else
            isReleased=false;
        if (Mouse::isButtonPressed(Mouse::Left))
            wasPressed=true;
        else
            wasPressed=false;

if (isF11Released)
        {
            if (isFullScreen)
            {
                window.create(VideoMode(1920, 1080), "Guns", Style::Default);
                isFullScreen=false;
            }
            else
            {
                window.create(VideoMode(1920, 1080), "Guns", Style::Fullscreen);
                isFullScreen=true;
            }
            window.setMouseCursorVisible(false);
            window.setSize(Vector2u(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));
            window.setPosition(Vector2i(0, 0));
        }
        if (game_state!=multiplayer)
        {
            socket.setBlocking(true);
        }


        if (game_state==game||game_state==multiplayer)
        {
            window.setMouseCursorVisible(false);
        }
        else
        {
            window.setMouseCursorVisible(true);
        }

    if (game_state==main_menu)
    {
        socket.setBlocking(true);
        window.draw(menu);

        if (arena_button.isPointed(pos))
        {
            arena_button.expand();
            if (isReleased)
            {
                for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].health=0;
                    }
                }
                mp=arena_map;
                player.gun_holding=primary;
                //setmapborders();
                player.health=player.max_health;
                player.position=spawn[rand()%6];
                player.position.speed.x=0;
                player.position.speed.y=0;
                //setmapborders();
                guns[primary].delay=0;
                guns[secondary].delay=0;
                guns[special].delay=0;
                guns[primary].predelay=0;
                guns[secondary].predelay=0;
                guns[special].predelay=0;
                guns[primary].reload_counter=0;
                guns[secondary].reload_counter=0;
                guns[special].reload_counter=0;
                guns[primary].ammo=guns[primary].max_ammo;
                guns[secondary].ammo=guns[secondary].max_ammo;
                guns[special].ammo=guns[special].max_ammo;
                //player.shield=player.max_shield;
//
                /*for (int i=4120; i<4320; i++)
                {
                    map0[960][i]=1;
                    map0[1920][i]=1;
                    map0[2880][i]=1;
                    map0[4800][i]=1;
                    map0[5760][i]=1;
                    map0[6720][i]=1;

                }
                for (int i=3360; i<4320; i++)
                {
                    map0[i][4000]=1;
                }*/


                //
                map_texture.loadFromFile("Textures/multiplayer_map.png");
                map_sprite.setTexture(map_texture);
                music.stop();
                music.openFromFile("Sounds/music/boss.wav");
                music.play();
                //sleep( seconds(1/60));
                game_state=game;
                isArena=true;
                wave=-1;
            }
        }
        else //game
        {
            arena_button.shrink();
        }
        window.draw(arena_button.sprite);

        if (connect_button.isPointed(pos))
        {
            connect_button.expand();
            if (isReleased)
            {
                //window.setSize(Vector2u(0, 0));
                window.setVisible(false);

                std::cout << "\nPort: 9999\nSelect connection type:\n[s] - server;\n[c] - client (requires IP address of a server);\n[any key] - none:\n";
                std::cin >> type;


                if(type == 's')
                {
                    std::cout << "Server is ready\n";
                    //ip = IpAddress::getLocalAddress();

                    /*std::cout << "IP: " << ip;
                    for (int i=0; i<100; i++)
                    {
                        std::cout << std::endl;
                    }
                    std::cout << "^^Scroll up to see IP address^^\n";*/

                    listener.listen(9999);

                    listener.accept(socket);/* != sf::Socket::Done)
        {
            std::cout << "\nError connecting\n";
        }*/
                }
                else if (type == 'c')
                {
                    std::cout << "Enter host ip:\n";
                    std::cin >> ip;

                    socket.connect(ip, 9999);
                }

                window.setVisible(true);
            }
        }
        else
        {
            connect_button.shrink();
        }


        window.draw(connect_button.sprite);
        if (multiplayer_button.isPointed(pos))
        {
            multiplayer_button.expand();
            if (isReleased&&(type=='s'||type=='c'))
            {
                for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].health=0;
                    }
                }
                mp=multiplayer_map;
                player.gun_holding=primary;
                //setmapborders();
                player.health=player.max_health;
                player.position=spawn[rand()%6];
                player.position.speed.x=0;
                player.position.speed.y=0;
                //setmapborders();
                guns[primary].delay=0;
                guns[secondary].delay=0;
                guns[special].delay=0;
                guns[primary].predelay=0;
                guns[secondary].predelay=0;
                guns[special].predelay=0;
                guns[primary].reload_counter=0;
                guns[secondary].reload_counter=0;
                guns[special].reload_counter=0;
                guns[primary].ammo=guns[primary].max_ammo;
                guns[secondary].ammo=guns[secondary].max_ammo;
                guns[special].ammo=guns[special].max_ammo;
                player.shield=player.max_shield;
//
                /*for (int i=4120; i<4320; i++)
                {
                    map0[960][i]=1;
                    map0[1920][i]=1;
                    map0[2880][i]=1;
                    map0[4800][i]=1;
                    map0[5760][i]=1;
                    map0[6720][i]=1;

                }
                for (int i=3360; i<4320; i++)
                {
                    map0[i][4000]=1;
                }*/


                //>>
                map_texture.loadFromFile("Textures/multiplayer_map.png");
                map_sprite.setTexture(map_texture);
                music.stop();
                music.openFromFile("Sounds/music/cave2.wav");
                music.play();
                game_state=multiplayer;
                packet.clear();






        //std::cout << "connect1";player.body
        //ghtf
        packet << ((prc(player.body.pos, 3)<0.5||prc(player.body.pos, 3)>2.5)&&player.step_counter<1) << player.isStanding << player.position.speed.x << player.reload_play << kb.speed.x << kb.speed.y << guns[player.gun_holding].predelay << guns[player.gun_holding].reload_counter << player.deploy << player.play << enemy_points << dmgEnemy << player.position.pos.x << player.position.pos.y << player.health << player.gun_holding << player.body.pos << pos.x-960 << pos.y-540 << player.tilt << guns[player.gun_holding].delay; //<< bullets << projectiles;
        for (int i=0; i<10; i++)
        {
            packet << bullets[i].length << bullets[i].rotation;
        }
        for (int i=0; i<projectile_count; i++)
        {
            //projectiles[i].damage=0;
            packet << projectiles[i].play << projectiles[i].x << projectiles[i].y << projectiles[i].damage << projectiles[i].rotation << projectiles[i].gun << projectiles[i].distance_left << projectiles[i].time;
        }
        //std::cout << "connect2";
        socket.send(packet);
        packet.clear();
        //std::cout << "c3";
}
        }
        else
        {
            multiplayer_button.shrink();
        }
        window.draw(multiplayer_button.sprite);

        if (shooting_range_button.isPointed(pos))
        {
            shooting_range_button.expand();
            if(isReleased)
            {
                for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].health=0;
                    }
                }
                enemy[1][0].position.pos.x=1440;
                enemy[1][1].position.pos.x=2400;
                enemy[1][2].position.pos.x=5280;
                enemy[1][3].position.pos.x=6240;
                enemy[1][4].position.pos.x=7200;
                for (int i=0; i<5; i++)
                {
                    enemy[1][i].position.pos.y=100;
                    enemy[1][i].position.speed.x=0;
                    enemy[1][i].position.speed.y=0;
                    enemy[1][i].health=enemy[1][i].max_health;
                }

                mp=shooting_range_map;
                victory_counter=120;
                player.gun_holding=primary;
                //setmapborders();
                player.health=player.max_health;
                player.position.pos.x=200;
                player.position.pos.y=200;
                player.position.speed.x=0;
                player.position.speed.y=0;
                //setmapborders();
                guns[primary].delay=0;
                guns[secondary].delay=0;
                guns[special].delay=0;
                guns[primary].predelay=0;
                guns[secondary].predelay=0;
                guns[special].predelay=0;
                guns[primary].reload_counter=0;
                guns[secondary].reload_counter=0;
                guns[special].reload_counter=0;
                guns[primary].ammo=guns[primary].max_ammo;
                guns[secondary].ammo=guns[secondary].max_ammo;
                guns[special].ammo=guns[special].max_ammo;


                map_texture.loadFromFile("Textures/shooting_range_map.png");
                map_sprite.setTexture(map_texture);
                music.stop();
                music.openFromFile("Sounds/music/menu.wav");
                music.play();
                game_state=game;
            }
        }
        else
        {
            shooting_range_button.shrink();
        }
        window.draw(shooting_range_button.sprite);

        if (start.isPointed(pos))
        {
            start.expand();
            if (isReleased)
            {
                game_state=choice;
            }
        }
        else
        {
            start.shrink();
        }
        window.draw(start.sprite);
        if (armory_button.isPointed(pos))
        {
            armory_button.expand();
            if (isReleased)
            {
                game_state=armory;
            }
        }
        else
        {
            armory_button.shrink();
        }
        window.draw(armory_button.sprite);
        if (quit.isPointed(pos))
        {
            quit.expand();
            if (isReleased)
            {
                return 0;
            }
        }
        else
        {
            quit.shrink();
        }
        window.draw(quit.sprite);
    }
    else if (game_state==choice)
    {
        window.draw(menu);
        //window.draw(map_button1);
        //window.draw(map_button2);
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            game_state=main_menu;
        }
        //sprite.setPosition(200, 200);
        if (comic_button[0].isPointed(pos))
        {
            comic_button[0].expand();
            if (isReleased)
            {
                game_state=comics;
                comic_texture.loadFromFile("Textures/comics/comic1.png");
                comic.setTexture(comic_texture);
            }
        }
        else
        {
            comic_button[0].shrink();
        }
        window.draw(comic_button[0].sprite);

        //sprite.setPosition(400, 200);
        if (level_button[0].isPointed(pos))
        {
            level_button[0].expand();

            if (isReleased)
            {
                for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].health=0;
                    }
                }
            victory_counter=120;
            player.gun_holding=primary;
            //setmapborders();
            player.health=player.max_health;
            player.position.pos.x=200;
            player.position.pos.y=200;
            player.position.speed.x=0;
            player.position.speed.y=0;
            guns[primary].delay=0;
                guns[secondary].delay=0;
                guns[special].delay=0;
                guns[primary].predelay=0;
                guns[secondary].predelay=0;
                guns[special].predelay=0;
                guns[primary].reload_counter=0;
                guns[secondary].reload_counter=0;
                guns[special].reload_counter=0;
                guns[primary].ammo=guns[primary].max_ammo;
                guns[secondary].ammo=guns[secondary].max_ammo;
                guns[special].ammo=guns[special].max_ammo;
    //enemy_damage=25;
    //enemy_guns_damage=5;
        mp=level[0];


    for (int i=0; i<5; i++)
    {
        enemy[0][i].position.pos.x = i*500+1570;
        enemy[0][i].position.pos.y=1000;
        enemy[0][i].position.speed.x=0;
        enemy[0][i].position.speed.y=0;
        enemy[0][i].health=enemy[0][i].max_health;
        //enemy[0][i].guns_delay=enemy[0][i].max_guns_delay;
    }
    enemy[0][0].delay=30;
    enemy[0][1].delay=25;
    enemy[0][2].delay=20;
    enemy[0][3].delay=15;
    enemy[0][4].delay=10;

            map_texture.loadFromFile("Textures/Map.png");
            map_sprite.setTexture(map_texture);
            game_state=game;
            music.stop();
            music.openFromFile("Sounds/music/beach.wav");
            music.play();
            }
        }
        else
        {
            level_button[0].shrink();
        }
        window.draw(level_button[0].sprite);
        sprite.setPosition(600, 200);
        if (level_button[1].isPointed(pos))
        {
            level_button[1].expand();
            if (isReleased)
            {
                for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].health=0;
                    }
                }
            victory_counter=120;
            player.gun_holding=primary;
            //setmapborders();
            player.position.pos.x=200;
            player.position.pos.y=200;
            player.position.speed.x=0;
            player.position.speed.y=0;


            player.health=player.max_health;
            guns[primary].delay=0;
                guns[secondary].delay=0;
                guns[special].delay=0;
            guns[primary].predelay=0;
                guns[secondary].predelay=0;
                guns[special].predelay=0;
                guns[primary].reload_counter=0;
                guns[secondary].reload_counter=0;
                guns[special].reload_counter=0;
                guns[primary].ammo=guns[primary].max_ammo;
                guns[secondary].ammo=guns[secondary].max_ammo;
                guns[special].ammo=guns[special].max_ammo;
                mp=level[1];
    /*for (int i=400; i<=1400; i++)
    {
        map0[i][3600]=1;
    }
    for (int i=1800; i<2800; i++)
    {
        map0[i][2880]=1;
    }*/
    for (int i=0; i<5; i++)
    {
        enemy[0][i].position.pos.x = i*500+1500;
        enemy[0][i].position.pos.y=1000;
        enemy[0][i].position.speed.x=0;
        enemy[0][i].position.speed.y=0;
        enemy[0][i].health=100;
    }


            map_texture.loadFromFile("Textures/map2.png");
            map_sprite.setTexture(map_texture);
            game_state=game;
            music.stop();
            music.openFromFile("Sounds/music/cave.wav");
            music.play();
            }
        }
        else
        {
            level_button[1].shrink();
        }
        window.draw(level_button[1].sprite);
        //sprite.setPosition(800, 200);
        if (level_button[2].isPointed(pos))
        {
            level_button[2].expand();

            if (isReleased)
            {
                victory_counter=120;
                player.gun_holding=primary;
                //setmapborders();
                player.position.pos.x=200;
                player.position.pos.y=200;
                player.position.speed.x=0;
                player.position.speed.y=0;
                player.health=player.max_health;
                guns[primary].delay=0;
                guns[secondary].delay=0;
                guns[special].delay=0;
                guns[primary].predelay=0;
                guns[secondary].predelay=0;
                guns[special].predelay=0;
                guns[primary].reload_counter=0;
                guns[secondary].reload_counter=0;
                guns[special].reload_counter=0;
                guns[primary].ammo=guns[primary].max_ammo;
                guns[secondary].ammo=guns[secondary].max_ammo;
                guns[special].ammo=guns[special].max_ammo;

                mp=level[2];

                map_texture.loadFromFile("Textures/map3.png");
                map_sprite.setTexture(map_texture);
                game_state=game;
                music.stop();
                music.openFromFile("Sounds/music/boss.wav");
                music.play();

                for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].health=0;
                    }
                }
                enemy[2][0].health=enemy[2][0].max_health;
                enemy[2][0].position.pos.x=3840;
                enemy[2][0].position.pos.y=4000;
                enemy[2][0].position.speed.x=0;
                enemy[2][0].position.speed.y=0;

            }
        }
        else
        {
            level_button[2].shrink();
        }
        window.draw(level_button[2].sprite);

        //sprite.setPosition(1000, 200);
        if (comic_button[1].isPointed(pos))
        {
            comic_button[1].expand();
            if (isReleased)
            {
                game_state=comics;
                comic_texture.loadFromFile("Textures/comics/comic2.png");
                comic.setTexture(comic_texture);
            }
        }
        else
        {
            comic_button[1].shrink();
        }
        window.draw(comic_button[1].sprite);

        //sprite.setPosition(200, 400);
        if (level_button[3].isPointed(pos))
        {
            level_button[3].expand();

            if (isReleased)
            {
                for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].health=0;
                    }
                }
            victory_counter=120;
            player.gun_holding=primary;
            //setmapborders();
            player.health=player.max_health;
            player.position.pos.x=200;
            player.position.pos.y=200;
            player.position.speed.x=0;
            player.position.speed.y=0;
            guns[primary].delay=0;
                guns[secondary].delay=0;
                guns[special].delay=0;
                guns[primary].predelay=0;
                guns[secondary].predelay=0;
                guns[special].predelay=0;
                guns[primary].reload_counter=0;
                guns[secondary].reload_counter=0;
                guns[special].reload_counter=0;
                guns[primary].ammo=guns[primary].max_ammo;
                guns[secondary].ammo=guns[secondary].max_ammo;
                guns[special].ammo=guns[special].max_ammo;
    //enemy_damage=25;
    //enemy_guns_damage=5;



            enemy[0][0].position.speed.x=0;
            enemy[0][0].position.speed.y=0;
            enemy[0][0].position.pos.x=1380;
            enemy[0][0].position.pos.y=3900;
            enemy[0][0].health=enemy[0][0].max_health;

            enemy[0][1].position.speed.x=0;
            enemy[0][1].position.speed.y=0;
            enemy[0][1].position.pos.x=1800;
            enemy[0][1].position.pos.y=3300;
            enemy[0][1].health=enemy[0][1].max_health;

            enemy[0][2].position.speed.x=0;
            enemy[0][2].position.speed.y=0;
            enemy[0][2].position.pos.x=2360;
            enemy[0][2].position.pos.y=3300;
            enemy[0][2].health=enemy[0][2].max_health;

            enemy[0][3].position.speed.x=0;
            enemy[0][3].position.speed.y=0;
            enemy[0][3].position.pos.x=2520;
            enemy[0][3].position.pos.y=3120;
            enemy[0][3].health=enemy[0][3].max_health;

            enemy[0][4].position.speed.x=0;
            enemy[0][4].position.speed.y=0;
            enemy[0][4].position.pos.x=2760;
            enemy[0][4].position.pos.y=3120;
            enemy[0][4].health=enemy[0][4].max_health;

            enemy[0][5].position.speed.x=0;
            enemy[0][5].position.speed.y=0;
            enemy[0][5].position.pos.x=3520;
            enemy[0][5].position.pos.y=4220;
            enemy[0][5].health=enemy[0][5].max_health;

            enemy[0][6].position.speed.x=0;
            enemy[0][6].position.speed.y=0;
            enemy[0][6].position.pos.x=4800;
            enemy[0][6].position.pos.y=4220;
            enemy[0][6].health=enemy[0][6].max_health;

            enemy[0][7].position.speed.x=0;
            enemy[0][7].position.speed.y=0;
            enemy[0][7].position.pos.x=5200;
            enemy[0][7].position.pos.y=4220;
            enemy[0][7].health=enemy[0][7].max_health;

            mp=level[3];


            map_texture.loadFromFile("Textures/map4.png");
            map_sprite.setTexture(map_texture);
            game_state=game;
            music.stop();
            music.openFromFile("Sounds/music/cave2.wav");
            music.play();
            }
        }
        else
        {
            level_button[3].shrink();
        }
        window.draw(level_button[3].sprite);
        //sprite.setPosition(400, 400);
        if (level_button[4].isPointed(pos))
        {
            level_button[4].expand();
            if (isReleased)
            {
                for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].health=0;
                    }
                }
                map_texture.loadFromFile("Textures/map5.png");
                map_sprite.setTexture(map_texture);
                victory_counter=120;
                player.gun_holding=primary;
                //setmapborders();
                player.health=player.max_health;
                player.position.pos.x=200;
                player.position.pos.y=200;
                player.position.speed.x=0;
                player.position.speed.y=0;
                guns[primary].delay=0;
                guns[secondary].delay=0;
                guns[special].delay=0;
                guns[primary].predelay=0;
                guns[secondary].predelay=0;
                guns[special].predelay=0;
                guns[primary].reload_counter=0;
                guns[secondary].reload_counter=0;
                guns[special].reload_counter=0;
                guns[primary].ammo=guns[primary].max_ammo;
                guns[secondary].ammo=guns[secondary].max_ammo;
                guns[special].ammo=guns[special].max_ammo;
                game_state=game;
                music.stop();
                music.openFromFile("Sounds/music/cave.wav");
                music.play();
                mp=level[4];
                enemy[0][0].position.speed.x=0;
                enemy[0][0].position.speed.y=0;
                enemy[0][0].position.pos.x=1360;
                enemy[0][0].position.pos.y=4220;
                enemy[0][0].health=enemy[0][0].max_health;

                enemy[3][0].position.speed.x=0;
                enemy[3][0].position.speed.y=0;
                enemy[3][0].position.pos.x=840;
                enemy[3][0].position.pos.y=3260;
                enemy[3][0].health=enemy[3][0].max_health;

                enemy[0][1].position.speed.x=0;
                enemy[0][1].position.speed.y=0;
                enemy[0][1].position.pos.x=2320;
                enemy[0][1].position.pos.y=2940;
                enemy[0][1].health=enemy[0][1].max_health;

                enemy[3][1].position.speed.x=0;
                enemy[3][1].position.speed.y=0;
                enemy[3][1].position.pos.x=2480;
                enemy[3][1].position.pos.y=2940;
                enemy[3][1].health=enemy[3][1].max_health;

                enemy[0][2].position.speed.x=0;
                enemy[0][2].position.speed.y=0;
                enemy[0][2].position.pos.x=2760;
                enemy[0][2].position.pos.y=2940;
                enemy[0][2].health=enemy[0][2].max_health;

                enemy[0][3].position.speed.x=0;
                enemy[0][3].position.speed.y=0;
                enemy[0][3].position.pos.x=3220;
                enemy[0][3].position.pos.y=3260;
                enemy[0][3].health=enemy[0][3].max_health;

                enemy[0][4].position.speed.x=0;
                enemy[0][4].position.speed.y=0;
                enemy[0][4].position.pos.x=3120;
                enemy[0][4].position.pos.y=3580;
                enemy[0][4].health=enemy[0][4].max_health;

                enemy[0][5].position.speed.x=0;
                enemy[0][5].position.speed.y=0;
                enemy[0][5].position.pos.x=3020;
                enemy[0][5].position.pos.y=4000;
                enemy[0][5].health=enemy[0][5].max_health;

                enemy[3][2].position.speed.x=0;
                enemy[3][2].position.speed.y=0;
                enemy[3][2].position.pos.x=4360;
                enemy[3][2].position.pos.y=2300;
                enemy[3][2].health=enemy[3][2].max_health;
            }
        }
        else
        {
            level_button[4].shrink();

        }
        window.draw(level_button[4].sprite);
        sprite.setPosition(600, 400);
        if (level_button[5].isPointed(pos))
        {
            level_button[5].expand();
            if (isReleased)
            {
                for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].health=0;
                    }
                }
                map_texture.loadFromFile("Textures/map6.png");
                map_sprite.setTexture(map_texture);
                victory_counter=120;
                player.gun_holding=primary;
                //setmapborders();
                player.health=player.max_health;
                player.position.pos.x=200;
                player.position.pos.y=200;
                player.position.speed.x=0;
                player.position.speed.y=0;
                guns[primary].delay=0;
                guns[secondary].delay=0;
                guns[special].delay=0;
                guns[primary].predelay=0;
                guns[secondary].predelay=0;
                guns[special].predelay=0;
                guns[primary].reload_counter=0;
                guns[secondary].reload_counter=0;
                guns[special].reload_counter=0;
                guns[primary].ammo=guns[primary].max_ammo;
                guns[secondary].ammo=guns[secondary].max_ammo;
                guns[special].ammo=guns[special].max_ammo;
                game_state=game;
                music.stop();
                music.openFromFile("Sounds/music/cave2.wav");
                music.play();
                mp=level[5];


                enemy[3][0].position.speed.x=0;
                enemy[3][0].position.speed.y=0;
                enemy[3][0].position.pos.x=4080;
                enemy[3][0].position.pos.y=4220;
                enemy[3][0].health=enemy[3][0].max_health;

                enemy[3][1].position.speed.x=0;
                enemy[3][1].position.speed.y=0;
                enemy[3][1].position.pos.x=3600;
                enemy[3][1].position.pos.y=4220;
                enemy[3][1].health=enemy[3][1].max_health;

                enemy[0][0].position.speed.x=0;
                enemy[0][0].position.speed.y=0;
                enemy[0][0].position.pos.x=7320;
                enemy[0][0].position.pos.y=3420;
                enemy[0][0].health=enemy[0][0].max_health;

                enemy[0][1].position.speed.x=0;
                enemy[0][1].position.speed.y=0;
                enemy[0][1].position.pos.x=7320;
                enemy[0][1].position.pos.y=2620;
                enemy[0][1].health=enemy[0][1].max_health;

                enemy[0][2].position.speed.x=0;
                enemy[0][2].position.speed.y=0;
                enemy[0][2].position.pos.x=7320;
                enemy[0][2].position.pos.y=1820;
                enemy[0][2].health=enemy[0][2].max_health;

                enemy[0][3].position.speed.x=0;
                enemy[0][3].position.speed.y=0;
                enemy[0][3].position.pos.x=7320;
                enemy[0][3].position.pos.y=1020;
                enemy[0][3].health=enemy[0][3].max_health;

                enemy[0][4].position.speed.x=0;
                enemy[0][4].position.speed.y=0;
                enemy[0][4].position.pos.x=7320;
                enemy[0][4].position.pos.y=220;
                enemy[0][4].health=enemy[0][4].max_health;

                enemy[0][5].position.speed.x=0;
                enemy[0][5].position.speed.y=0;
                enemy[0][5].position.pos.x=7560;
                enemy[0][5].position.pos.y=3020;
                enemy[0][5].health=enemy[0][5].max_health;

                enemy[0][6].position.speed.x=0;
                enemy[0][6].position.speed.y=0;
                enemy[0][6].position.pos.x=7560;
                enemy[0][6].position.pos.y=2220;
                enemy[0][6].health=enemy[0][6].max_health;

                enemy[0][7].position.speed.x=0;
                enemy[0][7].position.speed.y=0;
                enemy[0][7].position.pos.x=7560;
                enemy[0][7].position.pos.y=1420;
                enemy[0][7].health=enemy[0][7].max_health;

                enemy[3][2].position.speed.x=0;
                enemy[3][2].position.speed.y=0;
                enemy[3][2].position.pos.x=7560;
                enemy[3][2].position.pos.y=620;
                enemy[3][2].health=enemy[3][2].max_health;


            }
        }
        else
        {
            level_button[5].shrink();

        }
        window.draw(level_button[5].sprite);

        //sprite.setPosition(800, 400);
        if (level_button[6].isPointed(pos))
        {
            level_button[6].expand();
            if (isReleased)
            {
                for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].health=0;
                    }
                }
                map_texture.loadFromFile("Textures/map7.png");
                map_sprite.setTexture(map_texture);
                victory_counter=120;
                player.gun_holding=primary;
                //setmapborders();
                player.health=player.max_health;
                player.position.pos.x=200;
                player.position.pos.y=200;
                player.position.speed.x=0;
                player.position.speed.y=0;
                guns[primary].delay=0;
                guns[secondary].delay=0;
                guns[special].delay=0;
                guns[primary].predelay=0;
                guns[secondary].predelay=0;
                guns[special].predelay=0;
                guns[primary].reload_counter=0;
                guns[secondary].reload_counter=0;
                guns[special].reload_counter=0;
                guns[primary].ammo=guns[primary].max_ammo;
                guns[secondary].ammo=guns[secondary].max_ammo;
                guns[special].ammo=guns[special].max_ammo;
                game_state=game;
                music.stop();
                music.openFromFile("Sounds/music/boss.wav");
                music.play();
                mp=level[6];


                enemy[4][0].position.speed.x=0;
                enemy[4][0].position.speed.y=0;
                enemy[4][0].position.pos.x=3840;
                enemy[4][0].position.pos.y=620;
                enemy[4][0].health=enemy[4][0].max_health;
            }
        }
        else
        {
            level_button[6].shrink();
        }
        window.draw(level_button[6].sprite);
    }

    else if (game_state==multiplayer)
    {//player.health=
        if (player.step_counter>0)
        {
            player.step_counter--;
        }
        if ((prc(player.body.pos, 3)<0.5||prc(player.body.pos, 3)>2.5)&&player.step_counter<1)
        {
            player.step_counter=max_step_counter;
            player.step_play=true;
        }
        else
        {
            player.step_play=false;
        }
        /*if (player.step_play)
        {
            step[rand()%step_count].sound.play();
        }*/
        if (player.gun_holding!=primary)
        {
            guns[primary].predelay=0;
            guns[primary].reload_counter=0;
        }
        if (player.gun_holding!=secondary)
        {
            guns[secondary].predelay=0;
            guns[secondary].reload_counter=0;
        }
        if (player.gun_holding!=special)
        {
            guns[special].predelay=0;
            guns[special].reload_counter=0;
        }
        if (guns[primary].delay>0)
                {
                    guns[primary].delay--;
                }
                if (guns[secondary].delay>0)
                {
                    guns[secondary].delay--;
                }
                if (guns[special].delay>0)
                {
                    guns[special].delay--;
                }

        socket.setBlocking(false);
        player.deploy-=sign(player.deploy);

        if (Mouse::isButtonPressed(Mouse::Left)&&guns[player.gun_holding].delay<1&&guns[player.gun_holding].predelay<1&&guns[player.gun_holding].deploy_counter<1&&guns[player.gun_holding].reload_counter<1&&player.deploy==0)
            {
                if (guns[player.gun_holding].ammo>=guns[player.gun_holding].ammo_used)
                {
                    guns[player.gun_holding].predelay=guns[player.gun_holding].max_predelay;
                }
                else if (guns[player.gun_holding].ammo_used>0)
                {
                    guns[player.gun_holding].reload_sound.play();
                    guns[player.gun_holding].reload_counter=guns[player.gun_holding].max_reload;
                    player.reload_play=true;
                }
            }


//enemy_player.body.sprite.setTextureRect

        if (player.shield>0)
        {
            player.shield--;
            player.health=player.max_health;
        }

        if (player.health<=0)
        {
            enemy_points++;
            for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {
                        enemy[i][j].health=0;
                    }
                }
                player.deploy=guns[player.gun_holding].max_deploy;
            victory_counter=120;
            //player.gun_holding=primary;
            player.health=player.max_health;
            player.position=spawn[rand()%6];
            player.position.speed.x=0;
            player.position.speed.y=0;
            guns[primary].ammo=guns[primary].max_ammo;
            guns[secondary].ammo=guns[secondary].max_ammo;
            guns[special].ammo=guns[special].max_ammo;

            guns[primary].delay=0;
                guns[secondary].delay=0;
                guns[special].delay=0;

                guns[primary].predelay=0;
                guns[secondary].predelay=0;
                guns[special].predelay=0;

                guns[primary].reload_counter=0;
                guns[secondary].reload_counter=0;
                guns[special].reload_counter=0;

                player.shield=player.max_shield;
        }


        player.position.engine(player.head_height, player.height, player.width, mp);
        player.position.speed.y+=gravity;


        map_sprite.setPosition(960-player.position.pos.x, 540-player.position.pos.y);
        if (((mp.M[round1(player.position.pos.x)-player.width-1][round1(player.position.pos.y)+player.height]>0&&player.position.speed.x<=-1&&mp.M[round1(player.position.pos.x)-player.width-1][round1(player.position.pos.y)+player.height-1]<=0)||(mp.M[round1(player.position.pos.x)+player.width+1][round1(player.position.pos.y)+player.height]>0&&player.position.speed.x>=1&&mp.M[round1(player.position.pos.x)+player.width+1][round1(player.position.pos.y)+player.height-1]<=0))&&player.position.speed.y>-1)
            {
                player.position.speed.y=-1;
                //player.position.speed.x=sign1(player.position.speed.x);multiplayer_map
            }

        /*if (player.position.speed_x>player.max_speed*guns[player.gun_holding].swiftness)
        {mp[map_now].
            player.position.speed_x=player.max_speed*guns[player.gun_holding].swiftness;
        }
        else if (player.position.speed_x<-player.max_speed*guns[player.gun_holding].swiftness)
        {
            player.position.speed_x=-player.max_speed*guns[player.gun_holding].swiftness;
        }*/

        int temp=round1(player.position.pos.x)+player.width;
            int temp2=round1(player.position.pos.y)+player.height+1;
            player.isStanding=false;
            for (int i=round1(player.position.pos.x)-player.width; i<=temp; i++)
            {
                for (int j=temp2; j<=temp2+2&&j<mp.height; j++)
                {
                    if (mp.M[i][j]>0)
                    {
                        player.isStanding=true;
                        break;
                    }
                }
            }
            if (player.step_play&&player.isStanding&&!(player.position.speed.x<0.1&&player.position.speed.x>-0.1))
            {
            //std::cout << rand()%step_count << " ";
                step[rand()%step_count].sound.play();
            }
            if (player.isStanding)
            {
                if (player.position.speed.x>0)
                {
                    if (player.position.speed.x-friction<=0)
                    {
                        player.position.speed.x=0;
                    }
                    else
                    {
                        player.position.speed.x-=friction;
                    }
                }
                else if (player.position.speed.x<0)
                {
                    if (player.position.speed.x-friction>=0)
                    {
                        player.position.speed.x=0;
                    }
                    else
                    {
                        player.position.speed.x+=friction;
                    }
                }
            }//window.draw
            if (Keyboard::isKeyPressed(Keyboard::Left)||Keyboard::isKeyPressed(Keyboard::A))
            {
                if (player.isStanding)
                {
                    if (player.position.speed.x-player.strafe_force>-player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x-=player.strafe_force;
                    }
                    else if (player.position.speed.x>-player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x=-player.max_speed*guns[player.gun_holding].swiftness;
                    }
                }
                else
                {
                    if (player.position.speed.x-player.air_strafe_force>-player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x-=player.air_strafe_force;
                    }
                    else if (player.position.speed.x>-player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x=-player.max_speed*guns[player.gun_holding].swiftness;
                    }
                }
            }
//player.tilt=
            if (Keyboard::isKeyPressed(Keyboard::Right)||Keyboard::isKeyPressed(Keyboard::D))
            {
                if (player.isStanding)
                {
                    if (player.position.speed.x+player.strafe_force<player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x+=player.strafe_force;
                    }
                    else if (player.position.speed.x<player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x=player.max_speed*guns[player.gun_holding].swiftness;
                    }
                }
                else
                {
                    if (player.position.speed.x+player.air_strafe_force<player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x+=player.air_strafe_force;
                    }
                    else if (player.position.speed.x<player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x=player.max_speed*guns[player.gun_holding].swiftness;
                    }
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::W)||Keyboard::isKeyPressed(Keyboard::Up)||Keyboard::isKeyPressed(Keyboard::Space))
            {
                if (player.isStanding)
                {
                    player.position.speed.y=-player.jump_force*guns[player.gun_holding].swiftness;
                }
            }

            player.tilt=-sign(player.body.pos-3)*(player.body.pos-3)/15+0.2;

            if ((player.position.speed.x<0.1&&player.position.speed.x>-0.1)||!player.isStanding)
            {
                player.tilt=0;
            }


            if (guns[player.gun_holding].predelay>0||guns[player.gun_holding].delay>0||guns[player.gun_holding].deploy_counter>0||guns[player.gun_holding].reload_counter>0)
            {
                player.tilt=0;
            }

        /*for (int i=0; i<guns_count; i++)
            {

                if (guns[i].delay)
                {
                    guns[i].delay--;
                }
            }*/
            if (Keyboard::isKeyPressed(Keyboard::Num1)&&player.gun_holding!=primary)
            {
                guns[player.gun_holding].reload_sound.stop();
                guns[player.gun_holding].sound.stop();
                player.gun_holding=primary;
                player.deploy=guns[player.gun_holding].max_deploy;

            }
            if (Keyboard::isKeyPressed(Keyboard::Num2)&&player.gun_holding!=secondary)
            {
                guns[player.gun_holding].reload_sound.stop();
                guns[player.gun_holding].sound.stop();
                player.gun_holding=secondary;
                player.deploy=guns[player.gun_holding].max_deploy;

            }
            if (Keyboard::isKeyPressed(Keyboard::Num3)&&player.gun_holding!=special)
            {
                guns[player.gun_holding].reload_sound.stop();
                guns[player.gun_holding].sound.stop();
                player.gun_holding=special;
                player.deploy=guns[player.gun_holding].max_deploy;

            }


            window.draw(map_sprite);


            /*bool isStanding=false;
        for (int i=-player.width; i<=player.width; i++)
        {
            if (map0[round1(player.position.x+i)][round1(player.position.y)+player.height+1]==1)
            {
            if (player.position.speed_x>0)
            {
                if (player.position.speed_x>friction)
                {
                    player.position.speed_x-=friction;
                }
                else
                {
                    player.position.speed_x=0;
                }
            }
            else if (player.position.speed_x<0)
            {
                if (player.position.speed_x<-friction)
                {
                    player.position.speed_x+=friction;
                }
                else
                {
                    player.position.speed_x=0;
                }
            }
            isStanding=true;
            break;
            }
        }*/



        /*guns[player.gun_holding].sprite1.setTextureRect(IntRect(guns[player.gun_holding].positionx[guns[player.gun_holding].delay], 0, guns[player.gun_holding].width, guns[player.gun_holding].height));
        guns[player.gun_holding].sprite2.setTextureRect(IntRect(guns[player.gun_holding].positionx[guns[player.gun_holding].delay], 0, guns[player.gun_holding].width, guns[player.gun_holding].height));
        guns[player.gun_holding].sprite3.setTextureRect(IntRect(guns[player.gun_holding].positionx[guns[player.gun_holding].delay], 0, guns[player.gun_holding].width, guns[player.gun_holding].height));
        guns[player.gun_holding].sprite4.setTextureRect(IntRect(guns[player.gun_holding].positionx[guns[player.gun_holding].delay], 0, guns[player.gun_holding].width, guns[player.gun_holding].height));

        guns[player.gun_holding].sprite1.setRotation(rt(pos.x-960, pos.y-540)+player.tilt+player.deploy*sign1(pos.x-960));
        guns[player.gun_holding].sprite2.setRotation(rt(pos.x-960, pos.y-540)+270+player.tilt+player.deploy*sign1(pos.x-960));
        guns[player.gun_holding].sprite3.setRotation(rt(pos.x-960, pos.y-540)+180+player.tilt+player.deploy*sign1(pos.x-960));
        guns[player.gun_holding].sprite4.setRotation(rt(pos.x-960, pos.y-540)+90+player.tilt+player.deploy*sign1(pos.x-960));

        guns[player.gun_holding].sprite1.setPosition(960, 540);
        guns[player.gun_holding].sprite2.setPosition(960, 540);
        guns[player.gun_holding].sprite3.setPosition(960, 540);
        guns[player.gun_holding].sprite4.setPosition(960, 540);

        player.head2.setRotation(rt(pos.x-960, pos.y-540)+270);
        player.head3.setRotation(rt(pos.x-960, pos.y-540)+180);



        player.hands[player.gun_holding].right1.setTextureRect(IntRect(guns[player.gun_holding].right_positionx[guns[player.gun_holding].delay], 0, 49, 49));
        player.hands[player.gun_holding].right2.setTextureRect(IntRect(guns[player.gun_holding].right_positionx[guns[player.gun_holding].delay], 0, 49, 49));
        player.hands[player.gun_holding].right3.setTextureRect(IntRect(guns[player.gun_holding].right_positionx[guns[player.gun_holding].delay], 0, 49, 49));
        player.hands[player.gun_holding].right4.setTextureRect(IntRect(guns[player.gun_holding].right_positionx[guns[player.gun_holding].delay], 0, 49, 49));

        if (guns[player.gun_holding].isPistol)
        {
            player.hands[player.gun_holding].right1.setRotation(player.tilt);
            player.hands[player.gun_holding].right2.setRotation(270+player.tilt);
            player.hands[player.gun_holding].right3.setRotation(180+player.tilt);
            player.hands[player.gun_holding].right4.setRotation(90+player.tilt);
        }
        else
        {
            player.hands[player.gun_holding].right1.setRotation(rt(pos.x-960, pos.y-540)+player.tilt+player.deploy*sign1(pos.x-960));
            player.hands[player.gun_holding].right2.setRotation(rt(pos.x-960, pos.y-540)+270+player.tilt+player.deploy*sign1(pos.x-960));
            player.hands[player.gun_holding].right3.setRotation(rt(pos.x-960, pos.y-540)+180+player.tilt+player.deploy*sign1(pos.x-960));
            player.hands[player.gun_holding].right4.setRotation(rt(pos.x-960, pos.y-540)+90+player.tilt+player.deploy*sign1(pos.x-960));
        }




        player.hands[player.gun_holding].left1.setTextureRect(IntRect(guns[player.gun_holding].left_positionx[guns[player.gun_holding].delay], 0, 49, 49));
        player.hands[player.gun_holding].left2.setTextureRect(IntRect(guns[player.gun_holding].left_positionx[guns[player.gun_holding].delay], 0, 49, 49));
        player.hands[player.gun_holding].left3.setTextureRect(IntRect(guns[player.gun_holding].left_positionx[guns[player.gun_holding].delay], 0, 49, 49));
        player.hands[player.gun_holding].left4.setTextureRect(IntRect(guns[player.gun_holding].left_positionx[guns[player.gun_holding].delay], 0, 49, 49));

        player.hands[player.gun_holding].left1.setRotation(rt(pos.x-960, pos.y-540)+player.tilt+player.deploy*sign1(pos.x-960));
        player.hands[player.gun_holding].left2.setRotation(rt(pos.x-960, pos.y-540)+270+player.tilt+player.deploy*sign1(pos.x-960));
        player.hands[player.gun_holding].left3.setRotation(rt(pos.x-960, pos.y-540)+180+player.tilt+player.deploy*sign1(pos.x-960));
        player.hands[player.gun_holding].left4.setRotation(rt(pos.x-960, pos.y-540)+90+player.tilt+player.deploy*sign1(pos.x-960));*/






        /*if (Mouse::isButtonPressed(Mouse::Left)&&guns[player.gun_holding].delay==0&&!player.deploy)
        {
            player.play=true;
            double spread=random(guns[player.gun_holding].spread);
            guns[player.gun_holding].sound.play();
            guns[player.gun_holding].delay=guns[player.gun_holding].max_delay;
            if (!guns[player.gun_holding].isProjectile)
            {

             bullet=shoot(enemy_player.position.x, enemy_player.position.y, enemy_player.head_height, enemy_player.height, enemy_player.width, spread+rotation(pos.x-960, pos.y-540), player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);




        if (bullet.hit)
            {
                dmgEnemy+=bullet.damage;
            }
            guns[player.gun_holding].bullet.setPosition(960, 540);

            guns[player.gun_holding].bullet.setScale(bullet.distance, sign1(pos.x-960));
                guns[player.gun_holding].bullet.setRotation(rotation(bullet.final_x-player.position.x, bullet.final_y-player.position.y)*57);

                window.draw(guns[player.gun_holding].bullet);
                for (int i=0; i<10; i++)
                {
                    if (bullets[i].length<0.5)
                    {
                        //bullets[i].gun=player.gun_holding;
                        bullets[i].length=bullet.distance;
                        bullets[i].rotation=rotation(bullet.final_x-player.position.x, bullet.final_y-player.position.y)*57;
                        break;
                    }
                }

            for (int k=1; k<=guns[player.gun_holding].pellets; k++)
            {

             bullet=shoot(enemy_player.position.x, enemy_player.position.y, enemy_player.head_height, enemy_player.height, enemy_player.width, spread+rotation(pos.x-960, pos.y-540)+guns[player.gun_holding].pellet_spread*k, player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                if (bullet.hit)
            {
                dmgEnemy+=bullet.damage;

            }

            guns[player.gun_holding].bullet.setPosition(960, 540);
            guns[player.gun_holding].bullet.setScale(bullet.distance, sign1(pos.x-960));
                guns[player.gun_holding].bullet.setRotation(rotation(bullet.final_x-player.position.x, bullet.final_y-player.position.y)*57);

                window.draw(guns[player.gun_holding].bullet);
                for (int i=0; i<10; i++)
                {
                    if (bullets[i].length<0.5)
                    {
                        //bullets[i].gun=player.gun_holding;
                        bullets[i].length=bullet.distance;
                        bullets[i].rotation=rotation(bullet.final_x-player.position.x, bullet.final_y-player.position.y)*57;
                        break;
                    }
                }



             bullet=shoot(enemy_player.position.x, enemy_player.position.y, enemy_player.head_height, enemy_player.height, enemy_player.width, spread+rotation(pos.x-960, pos.y-540)-guns[player.gun_holding].pellet_spread*k, player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                if (bullet.hit)
            {
                dmgEnemy+=bullet.damage;
            }

            guns[player.gun_holding].bullet.setPosition(960, 540);
            guns[player.gun_holding].bullet.setScale(bullet.distance, sign1(pos.x-960));
                guns[player.gun_holding].bullet.setRotation(rotation(bullet.final_x-player.position.x, bullet.final_y-player.position.y)*57);

                window.draw(guns[player.gun_holding].bullet);
                for (int i=0; i<10; i++)
                {
                    if (bullets[i].length<0.5)
                    {
                        //bullets[i].gun=player.gun_holding;
                        bullets[i].length=bullet.distance;
                        bullets[i].rotation=rotation(bullet.final_x-player.position.x, bullet.final_y-player.position.y)*57;
                        break;
                    }
                }


            }
            }
            else
            {
                int pr=-1;
                for (int i=0; i<projectile_count; i++)
                {
                    if (projectile[i].damage<=0&&projectile[i].time<=0)
                    {
                        pr=i;
                        break;
                    }
                }
                if (pr>=0)
                {
                    projectile[pr].multiplier=guns[player.gun_holding].splash_multiplier;
                    projectile[pr].gun=player.gun_holding;
                    projectile[pr].time=guns[player.gun_holding].max_projectile_time;
                    projectile[pr].damage=guns[player.gun_holding].damage;
                    projectile[pr].speed=guns[player.gun_holding].proj_speed;
                    projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread;
                    projectile[pr].x=player.position.x;
                    projectile[pr].y=player.position.y;
                    projectile[pr].radius=guns[player.gun_holding].radius;
                    projectile[pr].distance_left=guns[player.gun_holding].max_distance;
                    projectile[pr].acceleration=guns[player.gun_holding].proj_acceleration;
                    projectile[pr].explosion.setBuffer(guns[player.gun_holding].exp_buffer);
                    projectile[pr].sprite1.setTexture(guns[player.gun_holding].proj_texture1);
                    projectile[pr].sprite2.setTexture(guns[player.gun_holding].proj_texture2);
                    projectile[pr].sprite3.setTexture(guns[player.gun_holding].proj_texture3);
                    projectile[pr].sprite4.setTexture(guns[player.gun_holding].proj_texture4);
                    projectile[pr].sprite1.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_length, guns[player.gun_holding].proj_width));
                    projectile[pr].sprite2.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_width, guns[player.gun_holding].proj_length));
                    projectile[pr].sprite3.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_length, guns[player.gun_holding].proj_width));
                    projectile[pr].sprite4.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_width, guns[player.gun_holding].proj_length));
                    projectile[pr].sprite1.setRotation(projectile[pr].rotation*57);
                    projectile[pr].sprite2.setRotation(270+projectile[pr].rotation*57);
                    projectile[pr].sprite3.setRotation(180+projectile[pr].rotation*57);
                    projectile[pr].sprite4.setRotation(90+projectile[pr].rotation*57);
                    projectile[pr].blast.setTexture(guns[player.gun_holding].blast);
                    projectile[pr].blast.setTextureRect(IntRect(0, 0, 2*guns[player.gun_holding].radius, 2*guns[player.gun_holding].radius));
                }
                for (int i=1; i<=guns[player.gun_holding].pellets; i++)
                {
                    pr=-1;
                for (int i=0; i<projectile_count; i++)
                {
                    if (projectile[i].damage<=0&&projectile[i].time<=0)
                    {
                        pr=i;
                        break;
                    }
                }
                if (pr>=0)
                {
                    projectile[pr].multiplier=guns[player.gun_holding].splash_multiplier;
                    projectile[pr].gun=player.gun_holding;
                    projectile[pr].time=guns[player.gun_holding].max_projectile_time;
                    projectile[pr].damage=guns[player.gun_holding].damage;
                    projectile[pr].speed=guns[player.gun_holding].proj_speed;
                    projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread+i*guns[player.gun_holding].pellet_spread;
                    projectile[pr].x=player.position.x;
                    projectile[pr].y=player.position.y;
                    projectile[pr].radius=guns[player.gun_holding].radius;
                    projectile[pr].distance_left=guns[player.gun_holding].max_distance;
                    projectile[pr].acceleration=guns[player.gun_holding].proj_acceleration;
                    projectile[pr].explosion.setBuffer(guns[player.gun_holding].exp_buffer);
                    projectile[pr].sprite1.setTexture(guns[player.gun_holding].proj_texture1);
                    projectile[pr].sprite2.setTexture(guns[player.gun_holding].proj_texture2);
                    projectile[pr].sprite3.setTexture(guns[player.gun_holding].proj_texture3);
                    projectile[pr].sprite4.setTexture(guns[player.gun_holding].proj_texture4);
                    projectile[pr].sprite1.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_length, guns[player.gun_holding].proj_width));
                    projectile[pr].sprite2.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_width, guns[player.gun_holding].proj_length));
                    projectile[pr].sprite3.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_length, guns[player.gun_holding].proj_width));
                    projectile[pr].sprite4.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_width, guns[player.gun_holding].proj_length));
                    projectile[pr].sprite1.setRotation(projectile[pr].rotation*57);
                    projectile[pr].sprite2.setRotation(270+projectile[pr].rotation*57);
                    projectile[pr].sprite3.setRotation(180+projectile[pr].rotation*57);
                    projectile[pr].sprite4.setRotation(90+projectile[pr].rotation*57);
                    projectile[pr].blast.setTexture(guns[player.gun_holding].blast);
                    projectile[pr].blast.setTextureRect(IntRect(0, 0, 2*guns[player.gun_holding].radius, 2*guns[player.gun_holding].radius));
                }

                pr=-1;
                for (int i=0; i<projectile_count; i++)
                {
                    if (projectile[i].damage<=0&&projectile[i].time<=0)
                    {
                        pr=i;
                        break;
                    }
                }
                if (pr>=0)
                {
                    projectile[pr].multiplier=guns[player.gun_holding].splash_multiplier;
                    projectile[pr].gun=player.gun_holding;
                    projectile[pr].time=guns[player.gun_holding].max_projectile_time;
                    projectile[pr].damage=guns[player.gun_holding].damage;
                    projectile[pr].speed=guns[player.gun_holding].proj_speed;
                    projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread-i*guns[player.gun_holding].pellet_spread;
                    projectile[pr].x=player.position.x;
                    projectile[pr].y=player.position.y;
                    projectile[pr].radius=guns[player.gun_holding].radius;
                    projectile[pr].distance_left=guns[player.gun_holding].max_distance;
                    projectile[pr].acceleration=guns[player.gun_holding].proj_acceleration;
                    projectile[pr].explosion.setBuffer(guns[player.gun_holding].exp_buffer);
                    projectile[pr].sprite1.setTexture(guns[player.gun_holding].proj_texture1);
                    projectile[pr].sprite2.setTexture(guns[player.gun_holding].proj_texture2);
                    projectile[pr].sprite3.setTexture(guns[player.gun_holding].proj_texture3);
                    projectile[pr].sprite4.setTexture(guns[player.gun_holding].proj_texture4);
                    projectile[pr].sprite1.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_length, guns[player.gun_holding].proj_width));
                    projectile[pr].sprite2.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_width, guns[player.gun_holding].proj_length));
                    projectile[pr].sprite3.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_length, guns[player.gun_holding].proj_width));
                    projectile[pr].sprite4.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_width, guns[player.gun_holding].proj_length));
                    projectile[pr].sprite1.setRotation(projectile[pr].rotation*57);
                    projectile[pr].sprite2.setRotation(270+projectile[pr].rotation*57);
                    projectile[pr].sprite3.setRotation(180+projectile[pr].rotation*57);
                    projectile[pr].sprite4.setRotation(90+projectile[pr].rotation*57);
                    projectile[pr].blast.setTexture(guns[player.gun_holding].blast);
                    projectile[pr].blast.setTextureRect(IntRect(0, 0, 2*guns[player.gun_holding].radius, 2*guns[player.gun_holding].radius));
                }
                }

            }
        }*/

            for (int k=0; k<projectile_count; k++)
            {
                if (projectile[k].damage<=0&&projectile[k].time)
                {
                    projectile[k].time--;
                    projectile[k].blast.setPR(1, round1(960-player.position.pos.x+projectile[k].x), round1(540-player.position.pos.y+projectile[k].y), 0);

                    projectile[k].blast.setFrame(projectile[k].time);
                    window.draw(projectile[k].blast.sprite);
                }
                if (projectile[k].damage>0)
                {
                    int dist=9999;
                Bullet bullet;
                Bullet subbullet;
                bullet.distance=0;
//multiplayer_map
                        if (enemy_player.health>0)
                        {
                            subbullet=shoot(enemy_player.position.pos.x, enemy_player.position.pos.y, enemy_player.head_height, enemy_player.height, enemy_player.width, projectile[k].rotation, projectile[k].x, projectile[k].y, projectile[k].damage, projectile[k].speed, mp);
                            if (subbullet.distance<dist)
                            {
                                bullet=subbullet;
                                dist=subbullet.distance;
                            }
                        }
                        else
                        {
                            bullet=shoot(0, 0, 0, 0, 0, projectile[k].rotation, projectile[k].x, projectile[k].y, projectile[k].damage, projectile[k].speed, mp);
                            dist=bullet.distance;
                        }

                    //mp[
                    if (dist<projectile[k].speed||projectile[k].distance_left<=0)
                    {


                        projectile[k].x+=(bullet.distance-1)*cos(projectile[k].rotation);
                        projectile[k].y+=(bullet.distance-1)*sin(projectile[k].rotation);
                        Bullet dmg=damage(projectile[k].multiplier, player.position.pos.x, player.position.pos.y, player.width, player.position.pos.y-player.head_height, player.position.pos.y+player.height, projectile[k].x, projectile[k].y, projectile[k].radius, projectile[k].damage, mp.M);

                        player.position.speed.x+=cos(rotation(dmg.final_x, dmg.final_y))*guns[projectile[k].gun].explosion_knockback*double(dmg.damage)/projectile[k].damage;
                        player.position.speed.y+=sin(rotation(dmg.final_x, dmg.final_y))*guns[projectile[k].gun].explosion_knockback*double(dmg.damage)/projectile[k].damage;
                        player.health-=round1(double(dmg.damage)*guns[projectile[k].gun].self_damage_multiplier);



                                if (enemy_player.health>0)
                                {
                                    dmg=damage(projectile[k].multiplier, enemy_player.position.pos.x, enemy_player.position.pos.y, enemy_player.width, enemy_player.position.pos.y-enemy_player.head_height, enemy_player.position.pos.y+enemy_player.height, projectile[k].x, projectile[k].y, projectile[k].radius, projectile[k].damage, mp.M);
                                    dmgEnemy+=round1(dmg.damage);
                                    kb.speed.x+=cos(projectile[k].rotation)*projectile[k].knockback*double(dmg.damage)/projectile[k].damage;
                                    kb.speed.y+=sin(projectile[k].rotation)*projectile[k].knockback*double(dmg.damage)/projectile[k].damage;
                                    kb.speed.x+=cos(rotation(dmg.final_x, dmg.final_y))*guns[projectile[k].gun].explosion_knockback*double(dmg.damage)/projectile[k].damage;
                                    kb.speed.y+=sin(rotation(dmg.final_x, dmg.final_y))*guns[projectile[k].gun].explosion_knockback*double(dmg.damage)/projectile[k].damage;
                                }

                        projectile[k].damage=0;
                        projectile[k].explosion.setBuffer(guns[projectile[k].gun].exp_buffer);
                        projectile[k].explosion.play();
                        //projectile[k].explosion.play();
                        projectile[k].blast.setPos(0.1);
                        projectile[k].blast.setPR(1, projectile[k].x, projectile[k].y, 0);
                        //window.draw(projectile[k].blast);
                    }
                    else
                    {
                        projectile[k].x+=cos(projectile[k].rotation)*(projectile[k].speed-1);
                        projectile[k].y+=sin(projectile[k].rotation)*(projectile[k].speed-1);
                        projectile[k].distance_left-=(projectile[k].speed-1);
                    }
                    //Mouse

                projectile[k].animation.setPR(sign1(cos(projectile[k].rotation)), 960+projectile[k].x-player.position.pos.x, 540+projectile[k].y-player.position.pos.y, rt(cos(projectile[k].rotation), sin(projectile[k].rotation)));
                projectile[k].animation.setFrame(round1(projectile[k].distance_left/projectile[k].speed));
                window.draw(projectile[k].animation.sprite);
                projectile[k].speed+=projectile[k].acceleration;
                }
                projectiles[k].gun=projectile[k].gun;
                projectiles[k].x=projectile[k].x;
                projectiles[k].y=projectile[k].y;
                projectiles[k].damage=projectile[k].damage;
                projectiles[k].rotation=projectile[k].rotation;
                projectiles[k].distance_left=projectile[k].distance_left;
                projectiles[k].time=projectile[k].time;
            }

            /*for (int k=0; k<projectile_count; k++)
            {
                //projectiles.projectile[k]=projectile[k];


                if (projectile[k].damage<=0)
            {
                if (projectile[k].time)
                {
                    projectile[k].time--;
                    projectile[k].blast.setPosition(960+projectile[k].x-player.position.x-projectile[k].radius,540+projectile[k].y-player.position.y-projectile[k].radius);
                    //enemy_projectiles.projectile[k].blast.setPosition(960+enemy_projectiles.projectile[k].x-player.position.x-enemy_projectiles.projectile[k].radius,540+enemy_projectiles.projectile[k].y-player.position.y-enemy_projectiles.projectile[k].radius);
                    window.draw(projectile[k].blast);
                    //window.draw(enemy_projectiles.projectile[k].blast);
                }
            }

            if (projectile[k].damage>0)
            {

            bullet.distance=0;


                        bullet=shoot(enemy_player.position.x, enemy_player.position.y, enemy_player.head_height, enemy_player.height, enemy_player.width, projectile[k].rotation, projectile[k].x, projectile[k].y, projectile[k].damage, projectile[k].speed);



            if (bullet.distance<projectile[k].speed||projectile[k].distance_left<=0)
            {
                projectile[k].x+=(bullet.distance-1)*cos(projectile[k].rotation);
                projectile[k].y+=(bullet.distance-1)*sin(projectile[k].rotation);
                        if (enemy_player.health>0)
                        {
                            dmgEnemy+=damage(projectile[k].multiplier, enemy_player.position.x, enemy_player.position.y, enemy_player.width, enemy_player.position.y-enemy_player.head_height, enemy_player.position.y+enemy_player.height, projectile[k].x, projectile[k].y, projectile[k].radius, projectile[k].damage);
                        }//health
                projectile[k].damage=0;
                projectile[k].explosion.play();
                projectile[k].blast.setPosition(960+projectile[k].x-player.position.x-projectile[k].radius,540+projectile[k].y-player.position.y-projectile[k].radius);
                projectiles[k].play=true;
                window.draw(projectile[k].blast);
            }
            else
            {
                projectile[k].x+=cos(projectile[k].rotation)*(projectile[k].speed-1);
                projectile[k].y+=sin(projectile[k].rotation)*(projectile[k].speed-1);
                projectile[k].distance_left-=(projectile[k].speed-1);
            }
            projectile[k].sprite1.setPosition(960+projectile[k].x-player.position.x,540+projectile[k].y-player.position.y);
            projectile[k].sprite2.setPosition(960+projectile[k].x-player.position.x,540+projectile[k].y-player.position.y);
            projectile[k].sprite3.setPosition(960+projectile[k].x-player.position.x,540+projectile[k].y-player.position.y);
            projectile[k].sprite4.setPosition(960+projectile[k].x-player.position.x,540+projectile[k].y-player.position.y);
            window.draw(projectile[k].sprite1);
            window.draw(projectile[k].sprite2);
            window.draw(projectile[k].sprite3);
            window.draw(projectile[k].sprite4);

            /*enemy_projectiles.projectile[k].sprite1.setPosition(960+enemy_projectiles.projectile[k].x-player.position.x,540+enemy_projectiles.projectile[k].y-player.position.y);
            enemy_projectiles.projectile[k].sprite2.setPosition(960+enemy_projectiles.projectile[k].x-player.position.x,540+enemy_projectiles.projectile[k].y-player.position.y);
            enemy_projectiles.projectile[k].sprite3.setPosition(960+enemy_projectiles.projectile[k].x-player.position.x,540+enemy_projectiles.projectile[k].y-player.position.y);
            enemy_projectiles.projectile[k].sprite4.setPosition(960+enemy_projectiles.projectile[k].x-player.position.x,540+enemy_projectiles.projectile[k].y-player.position.y);
            window.draw(enemy_projectiles.projectile[k].sprite1);
            window.draw(enemy_projectiles.projectile[k].sprite2);
            window.draw(enemy_projectiles.projectile[k].sprite3);
            window.draw(enemy_projectiles.projectile[k].sprite4);*/
            /*projectile[k].speed+=projectile[k].acceleration;
            }
            projectiles[k].gun=projectile[k].gun;
            projectiles[k].x=projectile[k].x;
            projectiles[k].y=projectile[k].y;
            projectiles[k].damage=projectile[k].damage;
            projectiles[k].rotation=projectile[k].rotation;
            projectiles[k].distance_left=projectile[k].distance_left;
            projectiles[k].time=projectile[k].time;
            }*/

            /*if (pos.x>=960)
        {
            if (Keyboard::isKeyPressed(Keyboard::D)&&!isStanding)
        {
            player.position.speed_x+=player.air_strafe_force;
        }
        if (Keyboard::isKeyPressed(Keyboard::A)&&!isStanding)
        {
            player.position.speed_x-=player.air_strafe_force;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)&&isStanding)
        {
            player.position.speed_x+=player.strafe_force;

            if (player.tilt>=10)
                {
                    player.tilt_speed=-1;
                }
                else if (player.tilt<=-10)
                {
                    player.tilt_speed=1;
                }
                player.tilt+=player.tilt_speed;
                if (player.body_frame_counter<29)
                    player.body_frame_counter++;
                else
                    player.body_frame_counter=0;

        }
        else if (Keyboard::isKeyPressed(Keyboard::A)&&isStanding)
        {
            player.position.speed_x-=player.strafe_force;


            if (player.tilt>=10)
                {
                    player.tilt_speed=-1;
                }
                else if (player.tilt<=-10)
                {
                    player.tilt_speed=1;
                }
                player.tilt+=player.tilt_speed;

                    if (player.body_frame_counter>0)
                    player.body_frame_counter--;
                else
                    player.body_frame_counter=29;
        }
        else
        {
            player.body_frame_counter=0;
            player.tilt=0;
            player.tilt_speed=1;
        }


            guns[player.gun_holding].sprite1.setScale(1, 1);
            guns[player.gun_holding].sprite2.setScale(1, 1);
            guns[player.gun_holding].sprite3.setScale(1, 1);
            guns[player.gun_holding].sprite4.setScale(1, 1);

            player.body1.setScale(1, 1);
            player.head2.setScale(1, 1);
            player.head3.setScale(1, 1);
            player.body4.setScale(1, 1);

            player.hands[player.gun_holding].left1.setScale(1, 1);
            player.hands[player.gun_holding].left2.setScale(1, 1);
            player.hands[player.gun_holding].left3.setScale(1, 1);
            player.hands[player.gun_holding].left4.setScale(1, 1);

            player.hands[player.gun_holding].right1.setScale(1, 1);
            player.hands[player.gun_holding].right2.setScale(1, 1);
            player.hands[player.gun_holding].right3.setScale(1, 1);
            player.hands[player.gun_holding].right4.setScale(1, 1);
        }
        else
        {
            if (Keyboard::isKeyPressed(Keyboard::D)&&!isStanding)
        {
            player.position.speed_x+=player.air_strafe_force;
        }
        if (Keyboard::isKeyPressed(Keyboard::A)&&!isStanding)
        {
            player.position.speed_x-=player.air_strafe_force;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)&&isStanding)
        {
            player.position.speed_x+=player.strafe_force;

            if (player.tilt>=10)
                {
                    player.tilt_speed=-1;
                }
                else if (player.tilt<=-10)
                {
                    player.tilt_speed=1;
                }
                player.tilt+=player.tilt_speed;
                if (player.body_frame_counter>0)
                    player.body_frame_counter--;
                else
                    player.body_frame_counter=29;
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)&&isStanding)
        {
            player.position.speed_x-=player.strafe_force;


            if (player.tilt>=10)
                {
                    player.tilt_speed=-1;
                }
                else if (player.tilt<=-10)
                {
                    player.tilt_speed=1;
                }
                player.tilt+=player.tilt_speed;
                if (player.body_frame_counter<29)
                    player.body_frame_counter++;
                else
                    player.body_frame_counter=0;
        }
        else
        {
            player.body_frame_counter=0;
            player.tilt=0;
            player.tilt_speed=-1;
        }

            guns[player.gun_holding].sprite1.setScale(-1, 1);
            guns[player.gun_holding].sprite2.setScale(1, -1);
            guns[player.gun_holding].sprite3.setScale(-1, 1);
            guns[player.gun_holding].sprite4.setScale(1, -1);

            player.body1.setScale(-1, 1);
            player.head2.setScale(1, -1);
            player.head3.setScale(-1, 1);
            player.body4.setScale(1, -1);

            player.hands[player.gun_holding].left1.setScale(-1, 1);
            player.hands[player.gun_holding].left2.setScale(1, -1);
            player.hands[player.gun_holding].left3.setScale(-1, 1);
            player.hands[player.gun_holding].left4.setScale(1, -1);

            player.hands[player.gun_holding].right1.setScale(-1, 1);
            player.hands[player.gun_holding].right2.setScale(1, -1);
            player.hands[player.gun_holding].right3.setScale(-1, 1);
            player.hands[player.gun_holding].right4.setScale(1, -1);
        }
        if ((Keyboard::isKeyPressed(Keyboard::W)||Keyboard::isKeyPressed(Keyboard::Space))&&isStanding)
        {
            player.position.speed_y-=player.jump_force*guns[player.gun_holding].swiftness;
        }*/


        /*if (isStanding)
        {
            player.body1.setTextureRect(IntRect(player.body_sprite_positionx[player.body_frame_counter], 0, 99, 99));
            player.body4.setTextureRect(IntRect(player.body_sprite_positionx[player.body_frame_counter], 0, 99, 99));
        }
        else
        {
            player.body1.setTextureRect(IntRect(300, 0, 100, 100));
            player.body4.setTextureRect(IntRect(300, 0, 100, 100));


        }


        if (isStanding)
        {
            enemy_player.body1.setTextureRect(IntRect(enemy_player.body_sprite_positionx[enemy_player.body_frame_counter], 0, 99, 99));
            enemy_player.body4.setTextureRect(IntRect(enemy_player.body_sprite_positionx[enemy_player.body_frame_counter], 0, 99, 99));
        }
        else
        {
            enemy_player.body1.setTextureRect(IntRect(300, 0, 100, 100));
            enemy_player.body4.setTextureRect(IntRect(300, 0, 100, 100));


        }*/
        if (Keyboard::isKeyPressed(Keyboard::R)&&guns[player.gun_holding].reload_counter<1&&guns[player.gun_holding].ammo_used>0)
            {
                if (guns[player.gun_holding].ammo<guns[player.gun_holding].max_ammo)
                {
                    guns[player.gun_holding].reload_sound.play();
                    guns[player.gun_holding].reload_counter=guns[player.gun_holding].max_reload;
                    player.reload_play=true;
                }
                //else std::cout << "AAAAAA ";

            }

            //player.body.setPR(1, 960, 540, 0);
                    //player.body.step(player.position.speed.x*(0.16/player.max_speed));

        if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (player.deploy)
            {
                player.tilt=double(player.deploy)/57;
            }

            if (guns[player.gun_holding].predelay>0)
            {

                guns[player.gun_holding].predelay--;
                guns[player.gun_holding].pre.setFrame(guns[player.gun_holding].predelay);
                guns[player.gun_holding].left_pre.setFrame(guns[player.gun_holding].predelay);
                guns[player.gun_holding].right_pre.setFrame(guns[player.gun_holding].predelay);

                if (guns[player.gun_holding].predelay<1)
                {
                    //shoot player.slot_holding=
                    guns[player.gun_holding].sound.play();
                    player.play=true;
                    guns[player.gun_holding].ammo-=guns[player.gun_holding].ammo_used;

                    guns[player.gun_holding].delay=guns[player.gun_holding].max_delay;
                    double spread=random(guns[player.gun_holding].spread);
                    if (guns[player.gun_holding].isProjectile) // fire projectile(s)
                    {
                        int pr=-1;
                        for (int j=0; j<projectile_count; j++)
                        {
                            if (projectile[j].damage<=0&&projectile[j].time<=0)
                            {
                                pr=j;
                                break;
                            }
                        }
                        if (pr>=0)
                        {//launches a projectile
                            projectile[pr].multiplier=guns[player.gun_holding].splash_multiplier;
                            projectile[pr].animation=guns[player.gun_holding].projectile;
                            projectile[pr].time=guns[player.gun_holding].max_projectile_time;
                            projectile[pr].damage=guns[player.gun_holding].damage;
                            projectile[pr].speed=guns[player.gun_holding].proj_speed;
                            projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread;
                            projectile[pr].x=player.position.pos.x;
                            projectile[pr].y=player.position.pos.y;
                            projectile[pr].radius=guns[player.gun_holding].radius;
                            projectile[pr].distance_left=guns[player.gun_holding].max_distance;
                            projectile[pr].acceleration=guns[player.gun_holding].proj_acceleration;
                            projectile[pr].blast=guns[player.gun_holding].blast;
                            projectile[pr].blast.setPos(0.1);
                            projectile[pr].knockback=guns[player.gun_holding].knockback;
                            projectile[pr].gun=player.gun_holding;

                        }
                        for (int i=1; i<=guns[player.gun_holding].pellets; i++)
                        {
                            pr=-1;
                        for (int j=0; j<projectile_count; j++)
                        {
                            if (projectile[j].damage<=0&&projectile[j].time<=0)
                            {
                                pr=j;
                                break;
                            }
                        }
                        if (pr>=0)
                        {//launches a projectile
                            projectile[pr].multiplier=guns[player.gun_holding].splash_multiplier;
                            projectile[pr].animation=guns[player.gun_holding].projectile;
                            projectile[pr].time=guns[player.gun_holding].max_projectile_time;
                            projectile[pr].damage=guns[player.gun_holding].damage;
                            projectile[pr].speed=guns[player.gun_holding].proj_speed;
                            projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread+i*guns[player.gun_holding].pellet_spread;
                            projectile[pr].x=player.position.pos.x;
                            projectile[pr].y=player.position.pos.y;
                            projectile[pr].radius=guns[player.gun_holding].radius;
                            projectile[pr].distance_left=guns[player.gun_holding].max_distance;
                            projectile[pr].acceleration=guns[player.gun_holding].proj_acceleration;
                            projectile[pr].blast=guns[player.gun_holding].blast;
                            projectile[pr].blast.setPos(0.1);
                            projectile[pr].knockback=guns[player.gun_holding].knockback;
                            projectile[pr].gun=player.gun_holding;

                        }
                        pr=-1;
                        for (int j=0; j<projectile_count; j++)
                        {
                            if (projectile[j].damage<=0&&projectile[j].time<=0)
                            {
                                pr=j;
                                break;
                            }
                        }
                        if (pr>=0)
                        {//launches a projectile
                            projectile[pr].multiplier=guns[player.gun_holding].splash_multiplier;
                            projectile[pr].animation=guns[player.gun_holding].projectile;
                            projectile[pr].time=guns[player.gun_holding].max_projectile_time;
                            projectile[pr].damage=guns[player.gun_holding].damage;
                            projectile[pr].speed=guns[player.gun_holding].proj_speed;
                            projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread-i*guns[player.gun_holding].pellet_spread;
                            projectile[pr].x=player.position.pos.x;
                            projectile[pr].y=player.position.pos.y;
                            projectile[pr].radius=guns[player.gun_holding].radius;
                            projectile[pr].distance_left=guns[player.gun_holding].max_distance;
                            projectile[pr].acceleration=guns[player.gun_holding].proj_acceleration;
                            projectile[pr].blast=guns[player.gun_holding].blast;
                            projectile[pr].blast.setPos(0.1);
                            projectile[pr].knockback=guns[player.gun_holding].knockback;
                            projectile[pr].gun=player.gun_holding;

                        }
                        }
                    }
                    else
                    {
                       int dist=9999;
                    Bullet bullet;
                    Bullet subbullet;
                    //int ty=0;
                    //int nb=0;


                    if (enemy_player.health>0)
                    {
                        subbullet=shoot(enemy_player.position.pos.x, enemy_player.position.pos.y, enemy_player.head_height, enemy_player.height, enemy_player.width, spread+rotation(pos.x-960, pos.y-540), player.position.pos.x, player.position.pos.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance, mp);
                        if (subbullet.hit&&subbullet.distance<dist)
                        {
                            bullet=subbullet;
                           // ty=i;
                            //nb=j;
                            dist=subbullet.distance;
                        }
                    }


            if (dist==9999)
            {
                subbullet=shoot(0, 0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540), player.position.pos.x, player.position.pos.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance, mp);
            }
            if (bullet.hit)
            {
                dmgEnemy+=bullet.damage;
                kb.speed.x+=cos(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y))*guns[player.gun_holding].knockback;
                kb.speed.y+=sin(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y))*guns[player.gun_holding].knockback;

                guns[player.gun_holding].bullet.setScale(bullet.distance, sign1(pos.x-960));
                guns[player.gun_holding].bullet.setRotation(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y)*57);
            }
            else
            {
               guns[player.gun_holding].bullet.setScale(subbullet.distance, sign1(pos.x-960));
               guns[player.gun_holding].bullet.setRotation(rotation(subbullet.final_x-player.position.pos.x, subbullet.final_y-player.position.pos.y)*57);
            }
            guns[player.gun_holding].bullet.setPosition(960, 540);
            for (int i=0; i<10; i++)
                {
                    if (bullets[i].length<0.5)
                    {
                        //bullets[i].gun=player.gun_holding;
                        bullets[i].length=subbullet.distance;
                        bullets[i].rotation=rotation(subbullet.final_x-player.position.pos.x, subbullet.final_y-player.position.pos.y);
                        break;
                    }
                }

//multiplayer_map
            window.draw(guns[player.gun_holding].bullet);

            for (int k=1; k<=guns[player.gun_holding].pellets; k++)
            {
                dist=9999;

                    if (enemy_player.health>0)
                    {//enemy[
                        subbullet=shoot(enemy_player.position.pos.x, enemy_player.position.pos.y, enemy_player.head_height, enemy_player.height, enemy_player.width, spread+rotation(pos.x-960, pos.y-540)+k*guns[player.gun_holding].pellet_spread, player.position.pos.x, player.position.pos.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance, mp);
                        if (subbullet.hit&&subbullet.distance<dist)
                        {
                            bullet=subbullet;
                            //ty=i;
                            //nb=j;
                            dist=subbullet.distance;
                        }
                    }

            //player.tiltmp[
            if (dist==9999)
            {
                subbullet=shoot(0, 0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540)+k*guns[player.gun_holding].pellet_spread, player.position.pos.x, player.position.pos.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance, mp);
            }
            if (bullet.hit)
            {
                dmgEnemy+=bullet.damage;
                kb.speed.x+=cos(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y+k*guns[player.gun_holding].pellet_spread))*guns[player.gun_holding].knockback;
                kb.speed.y+=sin(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y+k*guns[player.gun_holding].pellet_spread))*guns[player.gun_holding].knockback;

                guns[player.gun_holding].bullet.setScale(bullet.distance, sign1(pos.x-960));
                guns[player.gun_holding].bullet.setRotation(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y)*57/*+k*guns[player.gun_holding].pellet_spread*57*/);
            }
            else
            {
               guns[player.gun_holding].bullet.setScale(subbullet.distance, sign1(pos.x-960));
               guns[player.gun_holding].bullet.setRotation(rotation(subbullet.final_x-player.position.pos.x, subbullet.final_y-player.position.pos.y)*57/*+k*guns[player.gun_holding].pellet_spread*57*/);
            }
            guns[player.gun_holding].bullet.setPosition(960, 540);
            for (int i=0; i<10; i++)
                {
                    if (bullets[i].length<0.5)
                    {
                        //bullets[i].gun=player.gun_holding;
                        bullets[i].length=subbullet.distance;
                        bullets[i].rotation=rotation(subbullet.final_x-player.position.pos.x, subbullet.final_y-player.position.pos.y);
                        break;
                    }
                }


            window.draw(guns[player.gun_holding].bullet);
            dist=9999;

                    if (enemy_player.health>0)
                    {
                        subbullet=shoot(enemy_player.position.pos.x, enemy_player.position.pos.y, enemy_player.head_height, enemy_player.height, enemy_player.width, spread+rotation(pos.x-960, pos.y-540)-k*guns[player.gun_holding].pellet_spread, player.position.pos.x, player.position.pos.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance, mp);
                        if (subbullet.hit&&subbullet.distance<dist)
                        {
                            bullet=subbullet;
                            //ty=i;
                            //nb=j;
                            dist=subbullet.distance;
                        }
                    }


            if (dist==9999)
            {
                //subbullet=smp[hoot(0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540), player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                //subbullet=shoot(0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540)+k*guns[player.gun_holding].pellet_spread, player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                subbullet=shoot(0, 0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540)-k*guns[player.gun_holding].pellet_spread, player.position.pos.x, player.position.pos.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance, mp);

            }
            if (bullet.hit)
            {
                kb.speed.x+=cos(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y+k*guns[player.gun_holding].pellet_spread))*guns[player.gun_holding].knockback;
                kb.speed.y+=sin(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y+k*guns[player.gun_holding].pellet_spread))*guns[player.gun_holding].knockback;

                dmgEnemy+=bullet.damage;
                guns[player.gun_holding].bullet.setScale(bullet.distance, sign1(pos.x-960));
                guns[player.gun_holding].bullet.setRotation(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y)*57/*-k*guns[player.gun_holding].pellet_spread*57*/);
            }
            else
            {
               guns[player.gun_holding].bullet.setScale(subbullet.distance, sign1(pos.x-960));
               guns[player.gun_holding].bullet.setRotation(rotation(subbullet.final_x-player.position.pos.x, subbullet.final_y-player.position.pos.y)*57/*-k*guns[player.gun_holding].pellet_spread*57*/);
            }
            guns[player.gun_holding].bullet.setPosition(960, 540);
            for (int i=0; i<10; i++)
                {
                    if (bullets[i].length<0.5)
                    {
                        //bullets[i].gun=player.gun_holding;
                        bullets[i].length=subbullet.distance;
                        bullets[i].rotation=rotation(subbullet.final_x-player.position.pos.x, subbullet.final_y-player.position.pos.y);
                        break;
                    }
                }


            window.draw(guns[player.gun_holding].bullet);
            }

                    }
                    //

                    player.position.speed.x-=cos(rotation(pos.x-960, pos.y-540))*guns[player.gun_holding].self_knockback;
                    player.position.speed.y-=sin(rotation(pos.x-960, pos.y-540))*guns[player.gun_holding].self_knockback;
                }

                //

                //
                guns[player.gun_holding].pre.setFrame(guns[player.gun_holding].predelay);
                guns[player.gun_holding].left_pre.setFrame(guns[player.gun_holding].predelay);
                guns[player.gun_holding].right_pre.setFrame(guns[player.gun_holding].predelay);
                if (pos.x>=960)
                {

                    guns[player.gun_holding].pre.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left_pre.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));

                    guns[player.gun_holding].right_pre.setPR(1, 960, 540, player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));

                    player.body.setPR(1, 960, 540, 0);
                    player.body.step(player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                else
                {

                    guns[player.gun_holding].pre.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left_pre.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].right_pre.setPR(-1, 960, 540, -player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));
                    player.body.setPR(-1, 960, 540, 0);
                    player.body.step(-player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(-1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;

//.setPR
                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
                window.draw(guns[player.gun_holding].left_pre.sprite);
                window.draw(guns[player.gun_holding].pre.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(guns[player.gun_holding].right_pre.sprite);
            }
            else if (guns[player.gun_holding].reload_counter>0)
            {
                guns[player.gun_holding].reload_counter--;

                if (guns[player.gun_holding].reload_counter<1)
                {
                    if (guns[player.gun_holding].ammo+guns[player.gun_holding].max_load>=guns[player.gun_holding].max_ammo)
                    {
                        guns[player.gun_holding].ammo=guns[player.gun_holding].max_ammo;
                    }
                    else
                    {
                        guns[player.gun_holding].ammo+=guns[player.gun_holding].max_load;
                        if (!cancel)
                        {
                            guns[player.gun_holding].reload_sound.play();
                            guns[player.gun_holding].reload_counter=guns[player.gun_holding].max_reload;
                            player.reload_play=true;
                        }
                    }
                }
                guns[player.gun_holding].reload.setFrame(guns[player.gun_holding].reload_counter);
                guns[player.gun_holding].left_reload.setFrame(guns[player.gun_holding].reload_counter);
                guns[player.gun_holding].right_reload.setFrame(guns[player.gun_holding].reload_counter);
                if (pos.x>=960)
                {

                    guns[player.gun_holding].reload.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left_reload.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));

                    guns[player.gun_holding].right_reload.setPR(1, 960, 540, player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));

                    player.body.setPR(1, 960, 540, 0);
                    player.body.step(player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                else
                {

                    guns[player.gun_holding].reload.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left_reload.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].right_reload.setPR(-1, 960, 540, -player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));
                    player.body.setPR(-1, 960, 540, 0);
                    player.body.step(-player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(-1, 960, 540, rt(pos.x-960, pos.y-540));
                }

                if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }

                window.draw(guns[player.gun_holding].left_reload.sprite);
                window.draw(guns[player.gun_holding].reload.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(guns[player.gun_holding].right_reload.sprite);
            }
            else if (guns[player.gun_holding].deploy_counter>0)
            {
                guns[player.gun_holding].animation.setFrame(0);
                guns[player.gun_holding].left.setFrame(0);
                guns[player.gun_holding].right.setFrame(0);
                if (pos.x>=960)
                {

                    guns[player.gun_holding].animation.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));

                    guns[player.gun_holding].right.setPR(1, 960, 540, player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));

                    player.body.setPR(1, 960, 540, 0);
                    player.body.step(player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                else
                {

                    guns[player.gun_holding].animation.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].right.setPR(-1, 960, 540, -player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));
                    player.body.setPR(-1, 960, 540, 0);
                    player.body.step(-player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(-1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }

                window.draw(guns[player.gun_holding].left.sprite);
                window.draw(guns[player.gun_holding].animation.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(guns[player.gun_holding].right.sprite);
            }
            else
            {

                guns[player.gun_holding].animation.setFrame(guns[player.gun_holding].delay);
                guns[player.gun_holding].left.setFrame(guns[player.gun_holding].delay);
                guns[player.gun_holding].right.setFrame(guns[player.gun_holding].delay);
                if (pos.x>=960)
                {

                    guns[player.gun_holding].animation.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));

                    guns[player.gun_holding].right.setPR(1, 960, 540, player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));

                    player.body.setPR(1, 960, 540, 0);
                    player.body.step(player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                else
                {

                    guns[player.gun_holding].animation.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].right.setPR(-1, 960, 540, -player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));
                    player.body.setPR(-1, 960, 540, 0);
                    player.body.step(-player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(-1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }

                window.draw(guns[player.gun_holding].left.sprite);
                window.draw(guns[player.gun_holding].animation.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(guns[player.gun_holding].right.sprite);
            }
            if (guns[player.gun_holding].reload_counter<1)
            {
                cancel=false;
            }
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                cancel=true;
            }





            //window.draw(player.body.sprite);
            //window.draw(player.head.sprite);


//Mouse::



        health1=player.health;



        if (player.health>0)
        {
            health_text.setString(std::to_string(player.health));
            health.setScale((400*health1/player.max_health), 1);
        }
        else
        {
            health_text.setString("");
            health.setScale(0, 0);
        }
        window.draw(health);
        window.draw(health_text);


        /////////////

//health


//Packet rockets[100];


//Packet packet;

    enemy_points_string="Enemy: ";
    enemy_points_string+=std::to_string(enemy_points);

    points_string="You: ";
    points_string+=std::to_string(points);

    kills.setString(points_string);
    deaths.setString(enemy_points_string);
    //std::cout << "Test1";

 packet.clear();
    if (socket.receive(packet)==Socket::Done)
    {
        packet >> enemy_player.step_play;
        packet >> enemy_player.isStanding;
        packet >> enemy_player.position.speed.x;
        packet >> enemy_player.reload_play;
        packet >> player_kb.speed.x;
        packet >> player_kb.speed.y;
        packet >> enemy_player.pre;
        packet >> enemy_player.reload;
        packet >> enemy_player.deploy;
        packet >> enemy_player.play;
        packet >> points;
        packet >> dmgPlayer;
        packet >> enemy_player.position.pos.x;
        packet >> enemy_player.position.pos.y;
        packet >> enemy_player.health;
        packet >> enemy_player.gun_holding;
        packet >> enemy_player.body.pos;
        packet >> enemy_player.pos_x;
        packet >> enemy_player.pos_y;
        packet >> enemy_player.tilt;
        packet >> enemy_player.animation_delay; //>> enemy_bullets >> enemy_projectiles;
        for (int i=0; i<10; i++)
        {
            packet >> enemy_bullets[i].length >> enemy_bullets[i].rotation;
        }//100
        for (int i=0; i<projectile_count; i++)
        {
            //enemy_projectiles[i].damage=0;
            packet >> enemy_projectiles[i].play >> enemy_projectiles[i].x >> enemy_projectiles[i].y >> enemy_projectiles[i].damage >> enemy_projectiles[i].rotation >> enemy_projectiles[i].gun >> enemy_projectiles[i].distance_left >> enemy_projectiles[i].time;
        }
        packet.clear();
        //if (enemy_player.health<=0)
        //{
          //  dmgEnemy=0;
        //}
        packet << ((prc(player.body.pos, 3)<0.5||prc(player.body.pos, 3)>2.5)&&player.step_counter<1);
        packet << player.isStanding;
        packet << player.position.speed.x;
        packet << player.reload_play;
        packet << kb.speed.x;
        packet << kb.speed.y;
        packet << guns[player.gun_holding].predelay;
        packet << guns[player.gun_holding].reload_counter;
        packet << player.deploy;
        packet << player.play;
        packet << enemy_points;
        packet << dmgEnemy;
        packet << player.position.pos.x;
        packet << player.position.pos.y;
        packet << player.health;
        packet << player.gun_holding;
        packet << player.body.pos;
        packet << pos.x-960;
        packet << pos.y-540;
        packet << player.tilt;
        packet << guns[player.gun_holding].delay; //<< bullets << projectiles;
        for (int i=0; i<10; i++)
        {
            packet << bullets[i].length << bullets[i].rotation;
        }
        for (int i=0; i<projectile_count; i++)
        {
            //projectiles[i].damage=0;
            packet << projectiles[i].play << projectiles[i].x << projectiles[i].y << projectiles[i].damage << projectiles[i].rotation << projectiles[i].gun << projectiles[i].distance_left << projectiles[i].time;
        }
        socket.send(packet);
        packet.clear();
        hitstate=0;
        if (dmgEnemy>0)
        {
            if (dmgEnemy<enemy_player.health)
            {
                hitstate=1;
                hitsound.stop();
                hitsound.play();
            }
            else
            {
                hitstate=2;
                killsound.stop();
                killsound.play();
            }

        }
        dmgEnemy=0;
        player.health-=dmgPlayer;

        dmgPlayer=0;

        if (enemy_player.step_play&&enemy_player.isStanding&&!(enemy_player.position.speed.x<0.1&&enemy_player.position.speed.x>-0.1))
        {
            //std::cout << rand()%step_count << " ";
            step[rand()%step_count].sound.play();
            enemy_player.step_play=false;
        }

        for (int i=0; i<10; i++)
        {


            guns[enemy_player.gun_holding].bullet.setScale(enemy_bullets[i].length, sign1(cos(enemy_bullets[i].rotation)));
            guns[enemy_player.gun_holding].bullet.setRotation(enemy_bullets[i].rotation*57);
            guns[enemy_player.gun_holding].bullet.setPosition(enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540);
            //std::cout << enemy_player.gun_holding << " ";
            window.draw(guns[enemy_player.gun_holding].bullet);
            bullets[i].length=0;
        }//100
        for (int i=0; i<projectile_count; i++)
        {
            if (enemy_projectiles[i].play)
            {
                enemy_projectiles[i].explosion.setBuffer(guns[enemy_projectiles[i].gun].exp_buffer);
                enemy_projectiles[i].explosion.play();
                enemy_projectiles[i].play=false;
            }
            projectiles[i].damage=0;
            projectiles[i].play=false;
        }
        if (enemy_player.play)
        {
            enemy_player.weapon_sound=guns[enemy_player.gun_holding].sound;
            enemy_player.weapon_sound.play();
            enemy_player.play=false;
        }
        if (enemy_player.reload_play)
        {
            enemy_player.reload_sound=guns[enemy_player.gun_holding].reload_sound;
            enemy_player.reload_sound.play();
            enemy_player.reload_play=false;
        }
        player.play=false;
        player.reload_play=false;

        player.position.speed.x+=player_kb.speed.x;
        player.position.speed.y+=player_kb.speed.y;

        player_kb.speed.x=0;
        player_kb.speed.y=0;

        kb.speed.x=0;
        kb.speed.y=0;

    }






        /*if (player.health<=0)
        {reload_counter=
            for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy_count; j++)
                    {
                        enemy[i][j].health=0;
                    }
                }
            victory_counter=120;
            //player.gun_holding=primary;
            player.health=player.max_health;
            player.position.x=3840;
            player.position.y=200;
            player.position.speed_x=0;
            player.position.speed_y=0;
            guns[primary].delay=0;
                guns[secondary].delay=0;
                guns[special].delay=0;
        }


        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            for (int i=0; i<projectile_count; i++)
            {
                projectile[i].damage=0;
                projectile[i].time=0;
            }
            game_state=main_menu;
            music.stop();
            music.openFromFile("Sounds/music/menu.wav");
            music.play();
            break;
        }*/
        /*if (socket.Disconnected)
        {
            break;
        }*/



    /*while (socket.send(packet)!=Socket::Done)
    {
        if (clock.getElapsedTime().asMicroseconds()>16667)
        {
            break;
        }
if (player.health<=0||Keyboard::isKeyPressed(Keyboard::Escape))
        {
            for (int i=0; i<projectile_count; i++)
            {
                projectile[i].damage=0;
                projectile[i].time=0;
            }
            game_state=main_menu;
            music.stop();
            music.openFromFile("Sounds/music/menu.wav");
            music.play();
        }
    }*/


        ///////////// ////







        for (int k=0; k<projectile_count; k++)
            {

                //enemy_projectiles[k].explosion.setBuffer(guns[enemy_projectiles[k].gun].exp_buffer);

                    //enemy_projectiles[k].animation.setPR(sign1(cos(enemy_projectiles[k].rotation)), enemy_projectiles[k].x-player.position.pos.x+960, enemy_projectiles[k].y-player.position.pos.y+540, enemy_projectiles[k].rotation);



                //projectiles.projectile[k]=projectile[k];--


                if (enemy_projectiles[k].damage<=0)
            {
                if (enemy_projectiles[k].time>0)
                {
                    enemy_projectiles[k].blast=guns[enemy_projectiles[k].gun].blast;
                    enemy_projectiles[k].blast.setPR(1, enemy_projectiles[k].x-player.position.pos.x+960, enemy_projectiles[k].y-player.position.pos.y+540, 0);
                    enemy_projectiles[k].blast.setFrame(enemy_projectiles[k].time);
                    //enemy_projectiles.projectile[k].blast.setPosition(960+enemy_projectiles.projectile[k].x-player.position.x-enemy_projectiles.projectile[k].radius,540+enemy_projectiles.projectile[k].y-player.position.y-enemy_projectiles.projectile[k].radius);
                    window.draw(enemy_projectiles[k].blast.sprite);
                    //window.draw(enemy_projectiles.projectile[k].blast);
                }
            }

            if (enemy_projectiles[k].damage>0)
            {
                enemy_projectiles[k].animation=guns[enemy_projectiles[k].gun].projectile;
               // std::cout << "test1";

            /*bullet.distance=0;


                        bullet=shoot(enemy_player.position.x, enemy_player.position.y, enemy_player.head_height, enemy_player.height, enemy_player.width, projectile[k].rotation, projectile[k].x, projectile[k].y, projectile[k].damage, projectile[k].speed);



            if (bullet.distance<projectile[k].speed||projectile[k].distance_left<=0)
            {
                projectile[k].x+=(bullet.distance-1)*cos(projectile[k].rotation);
                projectile[k].y+=(bullet.distance-1)*sin(projectile[k].rotation);
                        if (enemy_player.health>0)
                        {
                            dmgEnemy+=damage(enemy_player.position.x, enemy_player.width, enemy_player.position.y-enemy_player.head_height, enemy_player.position.y+enemy_player.height, projectile[k].x, projectile[k].y, projectile[k].radius, projectile[k].damage);
                        }//health
                projectile[k].damage=0;
                projectile[k].explosion.play();
                projectile[k].blast.setPosition(960+projectile[k].x-player.position.x-projectile[k].radius,540+projectile[k].y-player.position.y-projectile[k].radius);
                window.draw(projectile[k].blast);
            }
            else
            {
                projectile[k].x+=cos(projectile[k].rotation)*(projectile[k].speed-1);
                projectile[k].y+=sin(projectile[k].rotation)*(projectile[k].speed-1);
                projectile[k].distance_left-=(projectile[k].speed-1);
            }*/
            enemy_projectiles[k].animation.setPR(sign1(cos(enemy_projectiles[k].rotation)), enemy_projectiles[k].x-player.position.pos.x+960, enemy_projectiles[k].y-player.position.pos.y+540, rt(cos(enemy_projectiles[k].rotation), sin(enemy_projectiles[k].rotation)));
                        enemy_projectiles[k].animation.setFrame(round1(enemy_projectiles[k].distance_left/guns[enemy_projectiles[k].gun].proj_speed));
                        window.draw(enemy_projectiles[k].animation.sprite);
                        //std::cout << "test2";

            /*enemy_projectiles.projectile[k].sprite1.setPosition(960+enemy_projectiles.projectile[k].x-player.position.x,540+enemy_projectiles.projectile[k].y-player.position.y);
            enemy_projectiles.projectile[k].sprite2.setPosition(960+enemy_projectiles.projectile[k].x-player.position.x,540+enemy_projectiles.projectile[k].y-player.position.y);
            enemy_projectiles.projectile[k].sprite3.setPosition(960+enemy_projectiles.projectile[k].x-player.position.x,540+enemy_projectiles.projectile[k].y-player.position.y);
            enemy_projectiles.projectile[k].sprite4.setPosition(960+enemy_projectiles.projectile[k].x-player.position.x,540+enemy_projectiles.projectile[k].y-player.position.y);
            window.draw(enemy_projectiles.projectile[k].sprite1);
            window.draw(enemy_projectiles.projectile[k].sprite2);
            window.draw(enemy_projectiles.projectile[k].sprite3);
            window.draw(enemy_projectiles.projectile[k].sprite4);*/

            }
            /*projectiles[k].x=projectile[k].x;
            projectiles[k].y=projectile[k].y;
            projectiles[k].damage=projectile[k].damage;
            projectiles[k].rotation=projectile[k].rotation;
            projectiles[k].distance_left=projectile[k].distance_left;
            projectiles[k].time=projectile[k].time;*/
            }


//std::cout << "1";


        //enemy_player.isStanding=false;

        /*for (int i=round1(enemy_player.position.pos.x-enemy_player.width); i<=enemy_player.position.pos.x+enemy_player.width; i++)
        {
            if (mp.M[i][round1(enemy_player.position.pos.y)+enemy_player.height+1]>0)
            {
                enemy_player.isStanding=true;
                break;
            }
        }*/
        //std::cout << "2";

            //animation.set

            //std::cout << "T";
        //enemy_player.body.step(0.0);
        //std::cout << "TEst";



        if (enemy_player.pre>0)
            {
                //std::cout << "Test_pre";


                guns[enemy_player.gun_holding].pre.setFrame(enemy_player.pre);
                guns[enemy_player.gun_holding].left_pre.setFrame(enemy_player.pre);
                guns[enemy_player.gun_holding].right_pre.setFrame(enemy_player.pre);





                //Mouse

                //
                if (enemy_player.pos_x>=0)
                {

                    guns[enemy_player.gun_holding].pre.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].left_pre.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].right_pre.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, enemy_player.tilt+!(guns[enemy_player.gun_holding].isPistol&&enemy_player.reload<1)*rt(enemy_player.pos_x, enemy_player.pos_y));
                    enemy_player.body.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, 0);
                    enemy_player.body.step(enemy_player.position.speed.x*(0.16/enemy_player.max_speed));
                    enemy_player.head.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, rt(enemy_player.pos_x, enemy_player.pos_y));
                }
                else
                {

                    guns[enemy_player.gun_holding].pre.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, -enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].left_pre.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, -enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].right_pre.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, -enemy_player.tilt+!(guns[enemy_player.gun_holding].isPistol&&enemy_player.reload<1)*rt(enemy_player.pos_x, enemy_player.pos_y));
                    enemy_player.body.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, 0);
                    enemy_player.body.step(-enemy_player.position.speed.x*(0.16/enemy_player.max_speed));
                    enemy_player.head.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, rt(enemy_player.pos_x, enemy_player.pos_y));
                }
                if (abs(enemy_player.position.speed.x)<0.1)
        {
            enemy_player.body.sprite.setTexture(enemy_player.idle);
            enemy_player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
        }
        if (!enemy_player.isStanding)
        {
            enemy_player.body.sprite.setTexture(enemy_player.jump);
            enemy_player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
        }

                window.draw(guns[enemy_player.gun_holding].left_pre.sprite);
                window.draw(guns[enemy_player.gun_holding].pre.sprite);

                window.draw(enemy_player.body.sprite);
                window.draw(enemy_player.head.sprite);

                window.draw(guns[enemy_player.gun_holding].right_pre.sprite);
                //std::cout << "test2";
            }
            else if (enemy_player.reload>0)
            {
                //std::cout << "Test_reload";
                guns[enemy_player.gun_holding].reload.setFrame(enemy_player.reload);
                guns[enemy_player.gun_holding].left_reload.setFrame(enemy_player.reload);
                guns[enemy_player.gun_holding].right_reload.setFrame(enemy_player.reload);

                if (enemy_player.pos_x>=0)
                {

                    guns[enemy_player.gun_holding].reload.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].left_reload.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));

                    guns[enemy_player.gun_holding].right_reload.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, enemy_player.tilt+!(guns[enemy_player.gun_holding].isPistol&&enemy_player.reload<1)*rt(enemy_player.pos_x, enemy_player.pos_y));

                    enemy_player.body.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, 0);
                    enemy_player.body.step(enemy_player.position.speed.x*(0.16/enemy_player.max_speed));
                    enemy_player.head.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, rt(enemy_player.pos_x, enemy_player.pos_y));
                }
                else
                {

                    guns[enemy_player.gun_holding].reload.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, -enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].left_reload.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, -enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].right_reload.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, -enemy_player.tilt+!(guns[enemy_player.gun_holding].isPistol&&enemy_player.reload<1)*rt(enemy_player.pos_x, enemy_player.pos_y));
                    enemy_player.body.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, 0);
                    enemy_player.body.step(-enemy_player.position.speed.x*(0.16/enemy_player.max_speed));
                    enemy_player.head.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, rt(enemy_player.pos_x, enemy_player.pos_y));
                }
                if (abs(enemy_player.position.speed.x)<0.1)
        {
            enemy_player.body.sprite.setTexture(enemy_player.idle);
            enemy_player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
        }
        if (!enemy_player.isStanding)
        {
            enemy_player.body.sprite.setTexture(enemy_player.jump);
            enemy_player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
        }

                window.draw(guns[enemy_player.gun_holding].left_reload.sprite);
                window.draw(guns[enemy_player.gun_holding].reload.sprite);

                window.draw(enemy_player.body.sprite);
                window.draw(enemy_player.head.sprite);

                window.draw(guns[enemy_player.gun_holding].right_reload.sprite);
                //std::cout << "test3";
            }
            else if (enemy_player.deploy>0)
            {
                //std::cout << "Test_deploy";
                guns[enemy_player.gun_holding].animation.setFrame(enemy_player.animation_delay);
                guns[enemy_player.gun_holding].left.setFrame(enemy_player.animation_delay);
                guns[enemy_player.gun_holding].right.setFrame(enemy_player.animation_delay);
                if (enemy_player.pos_x>=0)
                {

                    guns[enemy_player.gun_holding].animation.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].left.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));

                    guns[enemy_player.gun_holding].right.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, enemy_player.tilt+!(guns[enemy_player.gun_holding].isPistol&&enemy_player.reload<1)*rt(enemy_player.pos_x, enemy_player.pos_y));

                    enemy_player.body.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, 0);
                    enemy_player.body.step(enemy_player.position.speed.x*(0.16/enemy_player.max_speed));
                    enemy_player.head.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, rt(enemy_player.pos_x, enemy_player.pos_y));
                }
                else
                {

                    guns[enemy_player.gun_holding].animation.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, -enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].left.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, -enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].right.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, -enemy_player.tilt+!(guns[enemy_player.gun_holding].isPistol&&enemy_player.reload<1)*rt(enemy_player.pos_x, enemy_player.pos_y));
                    enemy_player.body.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, 0);
                    enemy_player.body.step(-enemy_player.position.speed.x*(0.16/enemy_player.max_speed));
                    enemy_player.head.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, rt(enemy_player.pos_x, enemy_player.pos_y));
                }
                if (abs(enemy_player.position.speed.x)<0.1)
        {
            enemy_player.body.sprite.setTexture(enemy_player.idle);
            enemy_player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
        }
        if (!enemy_player.isStanding)
        {
            enemy_player.body.sprite.setTexture(enemy_player.jump);
            enemy_player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
        }

                window.draw(guns[enemy_player.gun_holding].left.sprite);
                window.draw(guns[enemy_player.gun_holding].animation.sprite);

                window.draw(enemy_player.body.sprite);
                window.draw(enemy_player.head.sprite);

                window.draw(guns[enemy_player.gun_holding].right.sprite);
                //std::cout << "test5";
            }
            else
            {
                //std::cout << "TEst_delay";
                guns[enemy_player.gun_holding].animation.setFrame(enemy_player.animation_delay);
                guns[enemy_player.gun_holding].left.setFrame(enemy_player.animation_delay);
                guns[enemy_player.gun_holding].right.setFrame(enemy_player.animation_delay);
                if (enemy_player.pos_x>=0)
                {

                    guns[enemy_player.gun_holding].animation.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].left.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));

                    guns[enemy_player.gun_holding].right.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, enemy_player.tilt+!(guns[enemy_player.gun_holding].isPistol&&enemy_player.reload<1)*rt(enemy_player.pos_x, enemy_player.pos_y));

                    enemy_player.body.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, 0);
                    enemy_player.body.step(enemy_player.position.speed.x*(0.16/enemy_player.max_speed));
                    enemy_player.head.setPR(1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, rt(enemy_player.pos_x, enemy_player.pos_y));
                }
                else
                {

                    guns[enemy_player.gun_holding].animation.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, -enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].left.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, -enemy_player.tilt+rt(enemy_player.pos_x, enemy_player.pos_y));
                    guns[enemy_player.gun_holding].right.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, -enemy_player.tilt+!(guns[enemy_player.gun_holding].isPistol&&enemy_player.reload<1)*rt(enemy_player.pos_x, enemy_player.pos_y));
                    enemy_player.body.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, 0);
                    enemy_player.body.step(-enemy_player.position.speed.x*(0.16/enemy_player.max_speed));
                    enemy_player.head.setPR(-1, enemy_player.position.pos.x-player.position.pos.x+960, enemy_player.position.pos.y-player.position.pos.y+540, rt(enemy_player.pos_x, enemy_player.pos_y));
                }
                if (abs(enemy_player.position.speed.x)<0.1)
        {
            enemy_player.body.sprite.setTexture(enemy_player.idle);
            enemy_player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
        }
        if (!enemy_player.isStanding)
        {
            enemy_player.body.sprite.setTexture(enemy_player.jump);
            enemy_player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
        }

                window.draw(guns[enemy_player.gun_holding].left.sprite);
                window.draw(guns[enemy_player.gun_holding].animation.sprite);

                window.draw(enemy_player.body.sprite);
                window.draw(enemy_player.head.sprite);

                window.draw(guns[enemy_player.gun_holding].right.sprite);
                //std::cout << "TEstE";
            }














//std::cout << "Test1";






        window.draw(kills);
        window.draw(deaths);

        guns[primary].icon.setPosition(1320, 900);
        guns[secondary].icon.setPosition(1520, 900);
        guns[special].icon.setPosition(1720, 900);

        window.draw(guns[primary].icon);
        window.draw(guns[secondary].icon);
        window.draw(guns[special].icon);
        if (guns[primary].ammo_used>0)
        {
            t="";
            t+=std::to_string(guns[primary].ammo);
            t+="/";
            t+=std::to_string(guns[primary].max_ammo);
            t1.setString(t);
            t1.setPosition(1320, 1020);
            window.draw(t1);
        }
        if (guns[secondary].ammo_used>0)
        {
            t="";
            t+=std::to_string(guns[secondary].ammo);
            t+="/";
            t+=std::to_string(guns[secondary].max_ammo);
            t1.setString(t);
            t1.setPosition(1520, 1020);
            window.draw(t1);
        }
        if (guns[special].ammo_used>0)
        {
            t="";
            t+=std::to_string(guns[special].ammo);
            t+="/";
            t+=std::to_string(guns[special].max_ammo);
            t1.setString(t);
            t1.setPosition(1720, 1020);
            window.draw(t1);
        }



        if (player.gun_holding==primary)
        {
            frame.setPosition(1315, 895);
        }
        else if (player.gun_holding==secondary)
        {
            frame.setPosition(1515, 895);
        }
        else
        {
            frame.setPosition(1715, 895);
        }
        window.draw(frame);


        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            player.play=false;
            player.reload_play=false;
            dmgEnemy=0;
            enemy_points++;
            for (int i=0; i<projectile_count; i++)
            {
                projectile[i].damage=0;
                projectile[i].time=0;
                projectiles[i].play=false;
            }
            game_state=main_menu;
            music.stop();
            music.openFromFile("Sounds/music/menu.wav");
            music.play();
            player.deploy=guns[player.gun_holding].max_deploy;
        }

        guns[player.gun_holding].crosshair.setFrame(guns[player.gun_holding].delay);
        guns[player.gun_holding].crosshair.setPR(1, pos.x, pos.y, 0);
        window.draw(guns[player.gun_holding].crosshair.sprite);

        //std::cout << "Test3";
    }
//game_state=game
    else if (game_state==game)
    {
        if (player.step_counter>0)
        {
            player.step_counter--;
        }
        if ((prc(player.body.pos, 3)<0.5||prc(player.body.pos, 3)>2.5)&&player.step_counter<1)
        {
            player.step_counter=max_step_counter;
            player.step_play=true;
        }
        else
        {
            player.step_play=false;
        }
        //std::cout << player.step_play;
        //player.isStanding
        if (player.gun_holding!=primary)
        {
            guns[primary].predelay=0;
            guns[primary].reload_counter=0;
        }
        if (player.gun_holding!=secondary)
        {
            guns[secondary].predelay=0;
            guns[secondary].reload_counter=0;
        }
        if (player.gun_holding!=special)
        {
            guns[special].predelay=0;
            guns[special].reload_counter=0;
        }

        if (guns[primary].delay>0)
                {
                    guns[primary].delay--;
                }
                if (guns[secondary].delay>0)
                {
                    guns[secondary].delay--;
                }
                if (guns[special].delay>0)
                {
                    guns[special].delay--;
                }

        player.deploy-=sign(player.deploy);
        player.position.engine(player.head_height, player.height, player.width, mp);
        player.position.speed.y+=gravity;
        if (Mouse::isButtonPressed(Mouse::Left)&&guns[player.gun_holding].delay<1&&guns[player.gun_holding].predelay<1&&guns[player.gun_holding].deploy_counter<1&&guns[player.gun_holding].reload_counter<1&&player.deploy==0)
            {
                if (guns[player.gun_holding].ammo>=guns[player.gun_holding].ammo_used)
                {
                    guns[player.gun_holding].predelay=guns[player.gun_holding].max_predelay;
                }
                else if (guns[player.gun_holding].ammo_used>0)
                {
                    guns[player.gun_holding].reload_sound.play();
                    guns[player.gun_holding].reload_counter=guns[player.gun_holding].max_reload;
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::R)&&guns[player.gun_holding].reload_counter<1&&guns[player.gun_holding].ammo_used>0)
            {
                if (guns[player.gun_holding].ammo<guns[player.gun_holding].max_ammo)
                {
                    guns[player.gun_holding].reload_sound.play();
                    guns[player.gun_holding].reload_counter=guns[player.gun_holding].max_reload;
                    player.reload_play=true;
                }
                //else std::cout << "AAAAAA ";

            }


        int temp=round1(player.position.pos.x)+player.width;
            int temp2=round1(player.position.pos.y)+player.height+1;
            player.isStanding=false;
            for (int i=round1(player.position.pos.x)-player.width; i<=temp; i++)
            {
                for (int j=temp2; j<=temp2+2&&j<mp.height; j++)
                {
                    if (mp.M[i][j]>0)
                    {
                        player.isStanding=true;
                        break;
                    }
                }
            }
            if (player.step_play&&player.isStanding&&!(player.position.speed.x<0.1&&player.position.speed.x>-0.1))
            {
                //std::cout << rand()%step_count << " ";
                step[rand()%step_count].sound.play();
            }
            if (player.isStanding)
            {
                if (player.position.speed.x>0)
                {
                    if (player.position.speed.x-friction<=0)
                    {
                        player.position.speed.x=0;
                    }
                    else
                    {
                        player.position.speed.x-=friction;
                    }
                }
                else if (player.position.speed.x<0)
                {
                    if (player.position.speed.x-friction>=0)
                    {
                        player.position.speed.x=0;
                    }
                    else
                    {
                        player.position.speed.x+=friction;
                    }
                }
            }//window.draw
            if (Keyboard::isKeyPressed(Keyboard::Left)||Keyboard::isKeyPressed(Keyboard::A))
            {
                if (player.isStanding)
                {
                    if (player.position.speed.x-player.strafe_force>-player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x-=player.strafe_force;
                    }
                    else if (player.position.speed.x>-player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x=-player.max_speed*guns[player.gun_holding].swiftness;
                    }
                }
                else
                {
                    if (player.position.speed.x-player.air_strafe_force>-player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x-=player.air_strafe_force;
                    }
                    else if (player.position.speed.x>-player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x=-player.max_speed*guns[player.gun_holding].swiftness;
                    }
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::Right)||Keyboard::isKeyPressed(Keyboard::D))
            {
                if (player.isStanding)
                {
                    if (player.position.speed.x+player.strafe_force<player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x+=player.strafe_force;
                    }
                    else if (player.position.speed.x<player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x=player.max_speed*guns[player.gun_holding].swiftness;
                    }
                }
                else
                {
                    if (player.position.speed.x+player.air_strafe_force<player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x+=player.air_strafe_force;
                    }
                    else if (player.position.speed.x<player.max_speed*guns[player.gun_holding].swiftness)
                    {
                        player.position.speed.x=player.max_speed*guns[player.gun_holding].swiftness;
                    }
                }
            }

            if (Keyboard::isKeyPressed(Keyboard::W)||Keyboard::isKeyPressed(Keyboard::Up)||Keyboard::isKeyPressed(Keyboard::Space))
            {
                if (player.isStanding)
                {
                    player.position.speed.y=-player.jump_force*guns[player.gun_holding].swiftness;
                }
            }

            player.tilt=-sign(player.body.pos-3)*(player.body.pos-3)/15+0.2;

            if ((player.position.speed.x<0.1&&player.position.speed.x>-0.1)||!player.isStanding)
            {
                player.tilt=0;
            }


            if (guns[player.gun_holding].predelay>0||guns[player.gun_holding].delay>0||guns[player.gun_holding].deploy_counter>0||guns[player.gun_holding].reload_counter>0)
            {
                player.tilt=0;
            }



        //std::cout << player.position.speed_x << std::endl;
        //std::cout << "x:" << player.position.x << " " << player.position.speed_x << std::endl;
        //std::cout << "y:" << player.position.y << " " << player.position.speed_y << std::endl << std::endl;
        //player.position=engine(player.position, player.head_height, player.height, player.width);

        map_sprite.setPosition(960-player.position.pos.x, 540-player.position.pos.y);




//bulletfor(int i=0; i<guns_count;)
        /*for (int i=0; i<guns_count; i++)
            {

                if (guns[i].delay)
                {
                    guns[i].delay--;
                }
            }*/
            if (Keyboard::isKeyPressed(Keyboard::Num1)&&player.gun_holding!=primary)
            {
                guns[player.gun_holding].reload_sound.stop();
                guns[player.gun_holding].sound.stop();
                player.gun_holding=primary;
                player.deploy=guns[player.gun_holding].max_deploy;

            }
            if (Keyboard::isKeyPressed(Keyboard::Num2)&&player.gun_holding!=secondary)
            {
                guns[player.gun_holding].reload_sound.stop();
                guns[player.gun_holding].sound.stop();
                player.gun_holding=secondary;
                player.deploy=guns[player.gun_holding].max_deploy;

            }
            if (Keyboard::isKeyPressed(Keyboard::Num3)&&player.gun_holding!=special)
            {
                guns[player.gun_holding].reload_sound.stop();
                guns[player.gun_holding].sound.stop();
                player.gun_holding=special;
                player.deploy=guns[player.gun_holding].max_deploy;

            }



        /*if (player.body_frame_counter>=30)
        {
            player.body_frame_counter=0;
        }*/
        window.draw(map_sprite);
            for (int j=0; j<enemy[0][0].quantity; j++)
            {
                if (enemy[0][j].health>0)
                {
                    enemy[0][j].position.speed.y+=gravity;
                if (abs(enemy[0][j].position.pos.x-player.position.pos.x)<=enemy[0][j].sight_x&&abs(enemy[0][j].position.pos.y-player.position.pos.y)<=enemy[0][j].sight_y)
                {
                    if (enemy[0][j].delay)
                    {
                        enemy[0][j].guns_delay=enemy[0][j].max_guns_delay;
                        enemy[0][j].pos_x=player.position.pos.x-enemy[0][j].position.pos.x;
                        enemy[0][j].pos_y=player.position.pos.y-enemy[0][j].position.pos.y;
                        enemy[0][j].delay--;
                    }
                    else
                    {
                        enemy[0][j].guns_delay--;
                    }
                    enemy[0][j].isStanding=false;
                    for (int i=-enemy[0][j].width; i<=enemy[0][j].width; i++)
                    {
                        if (mp.M[round1(enemy[0][j].position.pos.x)+i][round1(enemy[0][j].position.pos.y)+enemy[0][j].height+1]>0)
                        {
                            enemy[0][j].isStanding=true;
                            break;
                        }
                    }//enemy[0][j].position.speed.y
                    if (enemy[0][j].isStanding)
                    {
                        if (enemy[0][j].jump_counter>0)
                        {
                            enemy[0][j].jump_counter--;
                        }



                        if (enemy[0][j].position.speed.x>0)
                {
                    if (enemy[0][j].pos_x>0)
                    {
                        enemy[0][j].body.step(enemy[0][j].position.speed.x*(0.16/enemy[0][j].max_speed));
                    }
                    else
                    {
                        enemy[0][j].body.step(-enemy[0][j].position.speed.x*(0.16/enemy[0][j].max_speed));
                    }
                    if (enemy[0][j].position.speed.x>friction)
                    {
                        enemy[0][j].position.speed.x-=friction;
                    }
                else
                {
                    enemy[0][j].position.speed.x=0;
                }
            }
            else if (enemy[0][j].position.speed.x<0)
            {
                if (enemy[0][j].pos_x<0)
                    {
                        enemy[0][j].body.step(enemy[0][j].position.speed.x*(0.16/enemy[0][j].max_speed));
                    }
                    else
                    {
                        enemy[0][j].body.step(-enemy[0][j].position.speed.x*(0.16/enemy[0][j].max_speed));
                    }
                if (enemy[0][j].position.speed.x<-friction)
                {
                    enemy[0][j].position.speed.x+=friction;
                }
                else
                {
                    enemy[0][j].position.speed.x=0;
                }
            }

                    int a1=round1(enemy[0][j].position.pos.x);
                    int c=round1(enemy[0][j].position.pos.y);
                    for (int i=c-enemy[0][j].head_height; i<c+enemy[0][j].height; i++)
                {
                    if ((mp.M[a1+enemy[0][j].width+1][i]==1||mp.M[a1-enemy[0][j].width-1][i]==1)&&enemy[0][j].jump_counter<=0)
                    {
                        enemy[0][j].position.speed.y-=enemy[0][j].jump_force;
                        enemy[0][j].jump_counter=30;
                        break;
                    }
                }
                if (abs(enemy[0][j].position.speed.x)<0.1)
                        {
                            enemy[0][j].body.sprite.setTexture(enemy[0][j].idle);
                            enemy[0][j].body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
                            enemy[0][j].body.pos=0.1;
                        }

                    }
                    else
                    {


                            enemy[0][j].body.sprite.setTexture(enemy[0][j].jump);
                            enemy[0][j].body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
                            enemy[0][j].body.pos=0.1;



                    }



                    if (enemy[0][j].position.pos.x>player.position.pos.x+100)
                    {
                        if (enemy[0][j].guns_delay==enemy[0][j].max_guns_delay)
                        {
                            if (mp.M[round1(enemy[0][j].position.pos.x)][round1(enemy[0][j].position.pos.y)+enemy[0][j].height+1]==1)
                            {
                                enemy[0][j].position.speed.x-=enemy[0][j].strafe_force;
                                //enemy[0][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[0][j].position.speed.x-=enemy[0][j].air_strafe_force;
                                //enemy[0][j].body_frame_counter=0;
                            }
                        }
                    }
                    else if (enemy[0][j].position.pos.x<player.position.pos.x-100)
                    {
                    if (enemy[0][j].guns_delay==enemy[0][j].max_guns_delay)
                        {
                            if (mp.M[round1(enemy[0][j].position.pos.x)][round1(enemy[0][j].position.pos.y)+enemy[0][j].height+1]==1)
                            {
                                enemy[0][j].position.speed.x+=enemy[0][j].strafe_force;
                                //enemy[0][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[0][j].position.speed.x+=enemy[0][j].air_strafe_force;
                                //enemy[0][j].body_frame_counter=0;
                            }
                        }
                    }

                if (enemy[0][j].position.speed.x<-10&&enemy[0][j].isStanding)
                {
                        enemy[0][j].position.speed.x=-10;
                }

                if (enemy[0][j].position.speed.x>10&&enemy[0][j].isStanding)
                {
                        enemy[0][j].position.speed.x=10;
                }



                if (enemy[0][j].guns_delay==0)
                {
                    enemy[0][j].animation_delay=guns[enemy[0][j].gun_holding].max_delay;

                    enemy[0][j].weapon_sound.play();
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    bullet=enemy_shoot(player.position.pos.x, player.position.pos.y, player.head_height, player.height, player.width, rotation(enemy[0][j].pos_x, enemy[0][j].pos_y), enemy[0][j].position.pos.x, enemy[0][j].position.pos.y, guns[enemy[0][j].gun_holding].damage, guns[enemy[0][j].gun_holding].max_distance, mp);
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    if (bullet.hit)
                    {
                        player.health-=bullet.damage;
                        player.position.speed.x+=cos(rotation(bullet.final_x-enemy[0][j].position.pos.x, bullet.final_y-enemy[0][j].position.pos.y))*guns[enemy[0][j].gun_holding].knockback;
                        player.position.speed.y+=sin(rotation(bullet.final_x-enemy[0][j].position.pos.x, bullet.final_y-enemy[0][j].position.pos.y))*guns[enemy[0][j].gun_holding].knockback;
                    }
                    enemy[0][j].bullet.setPosition(960-player.position.pos.x+enemy[0][j].position.pos.x, 540-player.position.pos.y+enemy[0][j].position.pos.y);
                    enemy[0][j].bullet.setScale(bullet.distance, sign1(enemy[0][j].pos_x));
                    enemy[0][j].bullet.setRotation(rotation(enemy[0][j].pos_x, enemy[0][j].pos_y)*57);
                    window.draw(enemy[0][j].bullet);
                    enemy[0][j].guns_delay=enemy[0][j].max_guns_delay;
                    enemy[0][j].delay=enemy[0][j].max_delay;
                }
                enemy[0][j].body.setPR(sign1(enemy[0][j].pos_x), 960+enemy[0][j].position.pos.x-player.position.pos.x, 540+enemy[0][j].position.pos.y-player.position.pos.y, 0);

                enemy[0][j].head.setPR(sign1(enemy[0][j].pos_x), 960+enemy[0][j].position.pos.x-player.position.pos.x, 540+enemy[0][j].position.pos.y-player.position.pos.y, rt(enemy[0][j].pos_x, enemy[0][j].pos_y));

                guns[enemy[0][j].gun_holding].animation.setPR(sign1(enemy[0][j].pos_x), 960+enemy[0][j].position.pos.x-player.position.pos.x, 540+enemy[0][j].position.pos.y-player.position.pos.y, rt(enemy[0][j].pos_x, enemy[0][j].pos_y));

                enemy[0][j].left.setPR(sign1(enemy[0][j].pos_x), 960+enemy[0][j].position.pos.x-player.position.pos.x, 540+enemy[0][j].position.pos.y-player.position.pos.y, rt(enemy[0][j].pos_x, enemy[0][j].pos_y));
                enemy[0][j].right.setPR(sign1(enemy[0][j].pos_x), 960+enemy[0][j].position.pos.x-player.position.pos.x, 540+enemy[0][j].position.pos.y-player.position.pos.y, 0);


                    guns[enemy[0][j].gun_holding].animation.setFrame(enemy[0][j].animation_delay);
                    enemy[0][j].left.setFrame(enemy[0][j].animation_delay);
                    enemy[0][j].right.setFrame(enemy[0][j].animation_delay);













                window.draw(enemy[0][j].left.sprite);

                window.draw(guns[enemy[0][j].gun_holding].animation.sprite);


                window.draw(enemy[0][j].body.sprite);

                window.draw(enemy[0][j].head.sprite);







                window.draw(enemy[0][j].right.sprite);


                enemy_health.setPosition(enemy[0][j].position.pos.x-player.position.pos.x+860, enemy[0][j].position.pos.y-player.position.pos.y+440);
                health1=enemy[0][j].health;
                enemy_health.setScale((200*health1/enemy[0][j].max_health), 1);
                window.draw(enemy_health);




            }
            else
            {
                enemy[0][j].delay=enemy[0][j].max_delay;
            }


                    //enemy[0][j].position=engine(enemy[0][j].position, enemy[0][j].head_height, enemy[0][j].height);



                if (enemy[0][j].animation_delay)
                {
                    enemy[0][j].animation_delay--;
                }



                enemy[0][j].position.engine(enemy[0][j].head_height, enemy[0][j].height, enemy[0][j].width, mp);






                if (enemy[0][j].position.speed.x>enemy[0][j].max_speed&&enemy[0][j].isStanding)
                {
                    enemy[0][j].position.speed.x=enemy[0][j].max_speed;
                }
                else if (enemy[0][j].position.speed.x<-enemy[0][j].max_speed&&enemy[0][j].isStanding)
                {
                    enemy[0][j].position.speed.x=-enemy[0][j].max_speed;
                }

            }
            }
            for (int j=0; j<enemy[1][0].quantity; j++)
            {



            if (enemy[1][j].health>0)
            {

                enemy[1][j].position.engine(enemy[1][j].head_height, enemy[1][j].height, enemy[1][j].width, mp);
                enemy[1][j].position.speed.y+=gravity;

                enemy[1][j].body.setPR(1, 960+enemy[1][j].position.pos.x-player.position.pos.x, 540+enemy[1][j].position.pos.y-player.position.pos.y, 0);
                window.draw(enemy[1][j].body.sprite);
                enemy[1][j].head.setPR(1, 960+enemy[1][j].position.pos.x-player.position.pos.x, 540+enemy[1][j].position.pos.y-player.position.pos.y, 0);
                window.draw(enemy[1][j].head.sprite);

                enemy_health.setPosition(enemy[1][j].position.pos.x-player.position.pos.x+860, enemy[1][j].position.pos.y-player.position.pos.y+440);
                health1=enemy[1][j].health;
                enemy_health.setScale((200*health1/enemy[1][j].max_health), 1);
                window.draw(enemy_health);
                //enemy[1][j].position.engine(enemy[1][j].head_height, enemy[1][j].height, enemy[1][j].width, mp);
            }
            }
            for (int j=0; j<enemy[2][0].quantity; j++)
            {
                if (enemy[2][j].health>0)
                {
                    enemy[2][j].position.speed.y+=gravity;
                if (abs(enemy[2][j].position.pos.x-player.position.pos.x)<=enemy[2][j].sight_x&&abs(enemy[2][j].position.pos.y-player.position.pos.y)<=enemy[2][j].sight_y)
                {
                    if (enemy[2][j].delay)
                    {
                        enemy[2][j].shots_left=enemy[2][j].max_shots;
                        enemy[2][j].guns_delay=enemy[2][j].max_guns_delay;
                        enemy[2][j].pos_x=player.position.pos.x-enemy[2][j].position.pos.x;
                        enemy[2][j].pos_y=player.position.pos.y-enemy[2][j].position.pos.y;
                        enemy[2][j].delay--;
                    }
                    else
                    {
                        enemy[2][j].guns_delay--;
                    }
                    enemy[2][j].isStanding=false;
                    for (int i=-enemy[2][j].width; i<=enemy[2][j].width; i++)
                    {
                        if (mp.M[round1(enemy[2][j].position.pos.x)+i][round1(enemy[2][j].position.pos.y)+enemy[2][j].height+1]>0)
                        {
                            enemy[2][j].isStanding=true;
                            break;
                        }
                    }
                    if (enemy[2][j].isStanding)
                    {
                        if (enemy[2][j].jump_counter>0)
                        {
                            enemy[2][j].jump_counter--;
                        }



                        if (enemy[2][j].position.speed.x>0)
                {
                    if (enemy[2][j].pos_x>0)
                    {
                        enemy[2][j].body.step(enemy[2][j].position.speed.x*(0.16/enemy[2][j].max_speed));
                    }
                    else
                    {
                        enemy[2][j].body.step(-enemy[2][j].position.speed.x*(0.16/enemy[2][j].max_speed));
                    }
                    if (enemy[2][j].position.speed.x>friction)
                    {
                        enemy[2][j].position.speed.x-=friction;
                    }
                else
                {
                    enemy[2][j].position.speed.x=0;
                }
            }
            else if (enemy[2][j].position.speed.x<0)
            {
                if (enemy[2][j].pos_x<0)
                    {
                        enemy[2][j].body.step(enemy[2][j].position.speed.x*(0.16/enemy[2][j].max_speed));
                    }
                    else
                    {
                        enemy[2][j].body.step(-enemy[2][j].position.speed.x*(0.16/enemy[2][j].max_speed));
                    }
                if (enemy[2][j].position.speed.x<-friction)
                {
                    enemy[2][j].position.speed.x+=friction;
                }
                else
                {
                    enemy[2][j].position.speed.x=0;
                }
            }

                    int a1=round1(enemy[2][j].position.pos.x);
                    int c=round1(enemy[2][j].position.pos.y);
                    for (int i=c-enemy[2][j].head_height; i<c+enemy[2][j].height; i++)
                {
                    if ((mp.M[a1+enemy[2][j].width+1][i]==1||mp.M[a1-enemy[2][j].width-1][i]==1)&&enemy[2][j].jump_counter<=0)
                    {
                        enemy[2][j].position.speed.y-=enemy[2][j].jump_force;
                        enemy[2][j].jump_counter=30;
                        break;
                    }
                }
                if (abs(enemy[2][j].position.speed.x)<0.1)
                        {
                            enemy[2][j].body.sprite.setTexture(enemy[2][j].idle);
                            enemy[2][j].body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
                            enemy[2][j].body.pos=0.1;
                        }

                    }
                    else
                    {


                            enemy[2][j].body.sprite.setTexture(enemy[2][j].jump);
                            enemy[2][j].body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
                            enemy[2][j].body.pos=0.1;



                    }



                    if (enemy[2][j].position.pos.x>player.position.pos.x+100)
                    {
                        if (enemy[2][j].guns_delay==enemy[2][j].max_guns_delay)
                        {
                            if (mp.M[round1(enemy[2][j].position.pos.x)][round1(enemy[2][j].position.pos.y)+enemy[2][j].height+1]==1)
                            {
                                enemy[2][j].position.speed.x-=enemy[2][j].strafe_force;
                                //enemy[0][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[2][j].position.speed.x-=enemy[2][j].air_strafe_force;
                                //enemy[0][j].body_frame_counter=0;
                            }
                        }
                    }
                    else if (enemy[2][j].position.pos.x<player.position.pos.x-100)
                    {
                    if (enemy[2][j].guns_delay==enemy[2][j].max_guns_delay)
                        {
                            if (mp.M[round1(enemy[2][j].position.pos.x)][round1(enemy[2][j].position.pos.y)+enemy[2][j].height+1]==1)
                            {
                                enemy[2][j].position.speed.x+=enemy[2][j].strafe_force;
                                //enemy[0][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[2][j].position.speed.x+=enemy[2][j].air_strafe_force;
                                //enemy[0][j].body_frame_counter=0;
                            }
                        }
                    }

                if (enemy[2][j].position.speed.x<-10&&enemy[2][j].isStanding)
                {
                        enemy[2][j].position.speed.x=-10;
                }

                if (enemy[2][j].position.speed.x>10&&enemy[2][j].isStanding)
                {
                        enemy[2][j].position.speed.x=10;
                }



                if (enemy[2][j].guns_delay==0)
                {
                    enemy[2][j].shots_left--;
                    enemy[2][j].animation_delay=guns[enemy[2][j].gun_holding].max_delay;

                    enemy[2][j].weapon_sound.play();
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    bullet=enemy_shoot(player.position.pos.x, player.position.pos.y, player.head_height, player.height, player.width, rotation(enemy[2][j].pos_x, enemy[2][j].pos_y), enemy[2][j].position.pos.x, enemy[2][j].position.pos.y, guns[enemy[2][j].gun_holding].damage, guns[enemy[2][j].gun_holding].max_distance, mp);
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    if (bullet.hit)
                    {
                        player.health-=bullet.damage;
                        player.position.speed.x+=cos(rotation(bullet.final_x-enemy[2][j].position.pos.x, bullet.final_y-enemy[2][j].position.pos.y))*guns[enemy[2][j].gun_holding].knockback;
                        player.position.speed.y+=sin(rotation(bullet.final_x-enemy[2][j].position.pos.x, bullet.final_y-enemy[2][j].position.pos.y))*guns[enemy[2][j].gun_holding].knockback;
                    }
                    enemy[2][j].bullet.setPosition(960-player.position.pos.x+enemy[2][j].position.pos.x, 540-player.position.pos.y+enemy[2][j].position.pos.y);
                    enemy[2][j].bullet.setScale(bullet.distance, sign1(enemy[2][j].pos_x));
                    enemy[2][j].bullet.setRotation(rotation(enemy[2][j].pos_x, enemy[2][j].pos_y)*57);
                    window.draw(enemy[2][j].bullet);
                    enemy[2][j].guns_delay=enemy[2][j].max_guns_delay;
                    if (enemy[2][j].shots_left<=0)
                    {
                        enemy[2][j].delay=enemy[2][j].max_delay;
                    }



                }
                enemy[2][j].body.setPR(sign1(enemy[2][j].pos_x), 960+enemy[2][j].position.pos.x-player.position.pos.x, 540+enemy[2][j].position.pos.y-player.position.pos.y, 0);

                enemy[2][j].head.setPR(sign1(enemy[2][j].pos_x), 960+enemy[2][j].position.pos.x-player.position.pos.x, 540+enemy[2][j].position.pos.y-player.position.pos.y, rt(enemy[2][j].pos_x, enemy[2][j].pos_y));

                guns[enemy[2][j].gun_holding].animation.setPR(sign1(enemy[2][j].pos_x), 960+enemy[2][j].position.pos.x-player.position.pos.x, 540+enemy[2][j].position.pos.y-player.position.pos.y, rt(enemy[2][j].pos_x, enemy[2][j].pos_y));

                enemy[2][j].left.setPR(sign1(enemy[2][j].pos_x), 960+enemy[2][j].position.pos.x-player.position.pos.x, 540+enemy[2][j].position.pos.y-player.position.pos.y, rt(enemy[2][j].pos_x, enemy[2][j].pos_y));
                enemy[2][j].right.setPR(sign1(enemy[2][j].pos_x), 960+enemy[2][j].position.pos.x-player.position.pos.x, 540+enemy[2][j].position.pos.y-player.position.pos.y, rt(enemy[2][j].pos_x, enemy[2][j].pos_y));


                    guns[enemy[2][j].gun_holding].animation.setFrame(enemy[2][j].animation_delay);
                    enemy[2][j].left.setFrame(enemy[2][j].animation_delay);
                    enemy[2][j].right.setFrame(enemy[2][j].animation_delay);











                window.draw(enemy[2][j].left.sprite);

                window.draw(guns[enemy[2][j].gun_holding].animation.sprite);


                window.draw(enemy[2][j].body.sprite);

                window.draw(enemy[2][j].head.sprite);







                window.draw(enemy[2][j].right.sprite);


                enemy_health.setPosition(enemy[2][j].position.pos.x-player.position.pos.x+860, enemy[2][j].position.pos.y-player.position.pos.y+440);
                health1=enemy[2][j].health;
                enemy_health.setScale((200*health1/enemy[2][j].max_health), 1);
                window.draw(enemy_health);




            }
            else
            {
                enemy[2][j].delay=enemy[2][j].max_delay;
            }


                    //enemy[0][j].position=engine(enemy[0][j].position, enemy[0][j].head_height, enemy[0][j].height);



                if (enemy[2][j].animation_delay)
                {
                    enemy[2][j].animation_delay--;
                }



                enemy[2][j].position.engine(enemy[2][j].head_height, enemy[2][j].height, enemy[2][j].width, mp);






                if (enemy[2][j].position.speed.x>enemy[2][j].max_speed&&enemy[2][j].isStanding)
                {
                    enemy[2][j].position.speed.x=enemy[2][j].max_speed;
                }
                else if (enemy[2][j].position.speed.x<-enemy[2][j].max_speed&&enemy[2][j].isStanding)
                {
                    enemy[2][j].position.speed.x=-enemy[2][j].max_speed;
                }

            }
            }
                /*


            if (enemy[2][j].health>0)
                {
                if (abs(enemy[2][j].position.x-player.position.x)<=enemy[2][j].sight_x&&abs(enemy[2][j].position.y-player.position.y)<=enemy[2][j].sight_y)
                {
                    if (enemy[2][j].delay)
                    {
                        enemy[2][j].shots_left=enemy[2][j].max_shots;
                        enemy[2][j].guns_delay=enemy[2][j].max_guns_delay;
                        enemy[2][j].pos_x=player.position.x-enemy[2][j].position.x;
                        enemy[2][j].pos_y=player.position.y-enemy[2][j].position.y;
                        enemy[2][j].delay--;
                    }
                    else
                    {
                        enemy[2][j].guns_delay--;
                    }
                    bool isStanding=false;
                    for (int i=-enemy[2][j].width; i<=enemy[2][j].width; i++)
                    {
                        if (map0[round1(enemy[2][j].position.x)+i][round1(enemy[2][j].position.y)+enemy[2][j].height+1]>0)
                        {
                            isStanding=true;
                            break;
                        }
                    }
                    if (isStanding)
                    {
                        enemy[2][j].body1.setTextureRect(IntRect(enemy[2][j].body_sprite_positionx[enemy[2][j].body_frame_counter], 0, 99, 99));
                        enemy[2][j].body4.setTextureRect(IntRect(enemy[2][j].body_sprite_positionx[enemy[2][j].body_frame_counter], 0, 99, 99));

                        if (enemy[2][j].position.speed_x>0)
            {
                if (enemy[2][j].position.speed_x>friction)
                {
                    enemy[2][j].position.speed_x-=friction;
                }
                else
                {
                    enemy[2][j].position.speed_x=0;
                }
            }
            else if (enemy[2][j].position.speed_x<0)
            {
                if (enemy[2][j].position.speed_x<-friction)
                {
                    enemy[2][j].position.speed_x+=friction;
                }
                else
                {
                    enemy[2][j].position.speed_x=0;
                }
            }
            int a1=round1(enemy[2][j].position.x);
                    int c=round1(enemy[2][j].position.y);
                    for (int i=c-enemy[2][j].head_height; i<c+enemy[2][j].height; i++)
                {
                    if ((map0[a1+enemy[2][j].width+1][i]==1||map0[a1-enemy[2][j].width-1][i]==1))
                    {
                        enemy[2][j].position.speed_y-=enemy[2][j].jump_force;
                        break;
                    }
                }
                    }
                    else
                    {
                        enemy[2][j].body1.setTextureRect(IntRect(300, 0, 100, 100));
                        enemy[2][j].body4.setTextureRect(IntRect(300, 0, 100, 100));
                    }
                    if (enemy[2][j].position.x>player.position.x+100)
                    {
                        if (enemy[2][j].guns_delay==enemy[2][j].max_guns_delay)
                        {
                            if (map0[round1(enemy[2][j].position.x)][round1(enemy[2][j].position.y)+enemy[2][j].height+1]==1)
                            {
                                enemy[2][j].position.speed_x-=enemy[2][j].strafe_force;
                                enemy[2][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[2][j].position.speed_x-=enemy[2][j].air_strafe_force;
                                enemy[2][j].body_frame_counter=0;
                            }
                        }
                    }
                    else if (enemy[2][j].position.x<player.position.x-100)
                    {
                    if (enemy[2][j].guns_delay==enemy[2][j].max_guns_delay)
                        {
                            if (map0[round1(enemy[2][j].position.x)][round1(enemy[2][j].position.y)+enemy[2][j].height+1]==1)
                            {
                                enemy[2][j].position.speed_x+=enemy[2][j].strafe_force;
                                enemy[2][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[2][j].position.speed_x+=enemy[2][j].air_strafe_force;
                                enemy[2][j].body_frame_counter=0;
                            }
                        }

                    }

                if (enemy[2][j].position.speed_x<-10)
                {
                        enemy[2][j].position.speed_x=-10;
                }

                if (enemy[2][j].position.speed_x>10)
                {
                        enemy[2][j].position.speed_x=10;
                }
                if (enemy[2][j].body_frame_counter>=29)
                {
                    enemy[2][j].body_frame_counter=0;
                }
                else if (enemy[2][j].body_frame_counter<1)
                {
                    enemy[2][j].body_frame_counter=29;
                }
                if ((enemy[2][j].position.x>=player.position.x-100&&enemy[2][j].position.x<=player.position.x+100)||enemy[2][j].delay==0)
                {
                    enemy[2][j].body_frame_counter=0;
                }

                 if (enemy[2][j].guns_delay==0)
                {
                    enemy[2][j].shots_left--;

                    enemy[2][j].animation_delay=guns[enemy[2][j].gun_holding].max_delay;


                    enemy[2][j].weapon_sound.play();
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    bullet=enemy_shoot(player.position.x, player.position.y, player.head_height, player.height, player.width, rotation(enemy[2][j].pos_x, enemy[2][j].pos_y), enemy[2][j].position.x, enemy[2][j].position.y, guns[enemy[2][j].gun_holding].damage, guns[enemy[2][j].gun_holding].max_distance);
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    if (bullet.hit)
                    {
                        player.health-=bullet.damage;
                    }
                    enemy[2][j].bullet.setPosition(960-player.position.x+enemy[2][j].position.x, 540-player.position.y+enemy[2][j].position.y);
                    enemy[2][j].bullet.setScale(bullet.distance, -1);
                    enemy[2][j].bullet.setRotation(rotation(enemy[2][j].pos_x, enemy[2][j].pos_y)*57);
                    window.draw(enemy[2][j].bullet);
                    enemy[2][j].guns_delay=enemy[2][j].max_guns_delay;
                    if (enemy[2][j].shots_left<=0)
                    {
                        enemy[2][j].delay=enemy[2][j].max_delay;
                    }

                }
                enemy[2][j].body1.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                enemy[2][j].body4.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                enemy[2][j].head2.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                enemy[2][j].head3.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);

                guns[enemy[2][j].gun_holding].sprite1.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                guns[enemy[2][j].gun_holding].sprite2.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                guns[enemy[2][j].gun_holding].sprite3.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                guns[enemy[2][j].gun_holding].sprite4.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                enemy[2][j].hands[enemy[2][j].gun_holding].left1.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                enemy[2][j].hands[enemy[2][j].gun_holding].left2.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                enemy[2][j].hands[enemy[2][j].gun_holding].left3.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                enemy[2][j].hands[enemy[2][j].gun_holding].left4.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                enemy[2][j].hands[enemy[2][j].gun_holding].right1.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                enemy[2][j].hands[enemy[2][j].gun_holding].right2.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                enemy[2][j].hands[enemy[2][j].gun_holding].right3.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);
                enemy[2][j].hands[enemy[2][j].gun_holding].right4.setPosition(960+enemy[2][j].position.x-player.position.x, 540+enemy[2][j].position.y-player.position.y);



                    enemy[2][j].head1.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y));
                    enemy[2][j].head2.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y)+270);
                    enemy[2][j].head3.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y)+180);
                    enemy[2][j].head4.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y)+90);

                    guns[enemy[2][j].gun_holding].sprite1.setTextureRect(IntRect(guns[enemy[2][j].gun_holding].positionx[enemy[2][j].animation_delay], 0, guns[enemy[2][j].gun_holding].width, guns[enemy[2][j].gun_holding].height));
                    guns[enemy[2][j].gun_holding].sprite2.setTextureRect(IntRect(guns[enemy[2][j].gun_holding].positionx[enemy[2][j].animation_delay], 0, guns[enemy[2][j].gun_holding].width, guns[enemy[2][j].gun_holding].height));
                    guns[enemy[2][j].gun_holding].sprite3.setTextureRect(IntRect(guns[enemy[2][j].gun_holding].positionx[enemy[2][j].animation_delay], 0, guns[enemy[2][j].gun_holding].width, guns[enemy[2][j].gun_holding].height));
                    guns[enemy[2][j].gun_holding].sprite4.setTextureRect(IntRect(guns[enemy[2][j].gun_holding].positionx[enemy[2][j].animation_delay], 0, guns[enemy[2][j].gun_holding].width, guns[enemy[2][j].gun_holding].height));

                    guns[enemy[2][j].gun_holding].sprite1.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y));
                    guns[enemy[2][j].gun_holding].sprite2.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y)+270);
                    guns[enemy[2][j].gun_holding].sprite3.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y)+180);
                    guns[enemy[2][j].gun_holding].sprite4.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y)+90);

                    enemy[2][j].hands[enemy[2][j].gun_holding].left1.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y));
                    enemy[2][j].hands[enemy[2][j].gun_holding].left2.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y)+270);
                    enemy[2][j].hands[enemy[2][j].gun_holding].left3.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y)+180);
                    enemy[2][j].hands[enemy[2][j].gun_holding].left4.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y)+90);

                    if (guns[enemy[2][j].gun_holding].isPistol)
                    {
                        enemy[2][j].hands[enemy[2][j].gun_holding].right1.setRotation(0);
                        enemy[2][j].hands[enemy[2][j].gun_holding].right2.setRotation(270);
                        enemy[2][j].hands[enemy[2][j].gun_holding].right3.setRotation(180);
                        enemy[2][j].hands[enemy[2][j].gun_holding].right4.setRotation(90);
                    }
                    else
                    {
                        enemy[2][j].hands[enemy[2][j].gun_holding].right1.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y));
                        enemy[2][j].hands[enemy[2][j].gun_holding].right2.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y)+270);
                        enemy[2][j].hands[enemy[2][j].gun_holding].right3.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y)+180);
                        enemy[2][j].hands[enemy[2][j].gun_holding].right4.setRotation(rt(enemy[2][j].pos_x, enemy[2][j].pos_y)+90);
                    }



                        int a=sign1(enemy[2][j].pos_x);


                        enemy[2][j].body1.setScale(a, 1);
                        enemy[2][j].body4.setScale(1, a);
                        enemy[2][j].head2.setScale(1, a);
                        enemy[2][j].head3.setScale(a, 1);

                        guns[enemy[2][j].gun_holding].sprite1.setScale(a, 1);
                        guns[enemy[2][j].gun_holding].sprite2.setScale(1, a);
                        guns[enemy[2][j].gun_holding].sprite3.setScale(a, 1);
                        guns[enemy[2][j].gun_holding].sprite4.setScale(1, a);

                        enemy[2][j].hands[enemy[2][j].gun_holding].left1.setScale(a, 1);
                        enemy[2][j].hands[enemy[2][j].gun_holding].left2.setScale(1, a);
                        enemy[2][j].hands[enemy[2][j].gun_holding].left3.setScale(a, 1);
                        enemy[2][j].hands[enemy[2][j].gun_holding].left4.setScale(1, a);

                        enemy[2][j].hands[enemy[2][j].gun_holding].right1.setScale(a, 1);
                        enemy[2][j].hands[enemy[2][j].gun_holding].right2.setScale(1, a);
                        enemy[2][j].hands[enemy[2][j].gun_holding].right3.setScale(a, 1);
                        enemy[2][j].hands[enemy[2][j].gun_holding].right4.setScale(1, a);









                window.draw(enemy[2][j].hands[enemy[2][j].gun_holding].left1);
                window.draw(enemy[2][j].hands[enemy[2][j].gun_holding].left2);
                window.draw(enemy[2][j].hands[enemy[2][j].gun_holding].left3);
                window.draw(enemy[2][j].hands[enemy[2][j].gun_holding].left4);

                window.draw(enemy[2][j].body1);
                window.draw(enemy[2][j].body4);
                window.draw(enemy[2][j].head2);
                window.draw(enemy[2][j].head3);



                window.draw(guns[enemy[2][j].gun_holding].sprite1);
                window.draw(guns[enemy[2][j].gun_holding].sprite2);
                window.draw(guns[enemy[2][j].gun_holding].sprite3);
                window.draw(guns[enemy[2][j].gun_holding].sprite4);

                window.draw(enemy[2][j].hands[enemy[2][j].gun_holding].right1);
                window.draw(enemy[2][j].hands[enemy[2][j].gun_holding].right2);
                window.draw(enemy[2][j].hands[enemy[2][j].gun_holding].right3);
                window.draw(enemy[2][j].hands[enemy[2][j].gun_holding].right4);

                enemy_health.setPosition(enemy[2][j].position.x-player.position.x+860, enemy[2][j].position.y-player.position.y+440);
                health1=enemy[2][j].health;
                enemy_health.setScale((200*health1/enemy[2][j].max_health), 1);
                window.draw(enemy_health);




            }

            else
            {
                enemy[2][j].delay=enemy[2][j].max_delay;
            }


                    //enemy[0][j].position=engine(enemy[0][j].position, enemy[0][j].head_height, enemy[0][j].height);



                if (enemy[2][j].animation_delay)
                {
                    enemy[2][j].animation_delay--;
                }



                enemy[2][j].position=engine(enemy[2][j].position, enemy[2][j].head_height, enemy[2][j].height, enemy[2][j].width);








                if (enemy[2][j].position.speed_x>enemy[2][j].max_speed)
                {
                    enemy[2][j].position.speed_x=enemy[2][j].max_speed;
                }
                else if (enemy[2][j].position.speed_x<-enemy[2][j].max_speed)
                {
                    enemy[2][j].position.speed_x=-enemy[2][j].max_speed;
                }

            }
            else
            {
                enemy[2][j].delay=enemy[2][j].max_delay;
            }
            }
            */
            for (int j=0; j<enemy[3][0].quantity; j++)
            {
                if (enemy[3][j].health>0)
                {
                    enemy[3][j].position.speed.y+=gravity;
                if (abs(enemy[3][j].position.pos.x-player.position.pos.x)<=enemy[3][j].sight_x&&abs(enemy[3][j].position.pos.y-player.position.pos.y)<=enemy[3][j].sight_y)
                {
                    if (enemy[3][j].delay)
                    {
                        enemy[3][j].guns_delay=enemy[3][j].max_guns_delay;
                        enemy[3][j].pos_x=player.position.pos.x-enemy[3][j].position.pos.x;
                        enemy[3][j].pos_y=player.position.pos.y-enemy[3][j].position.pos.y;
                        enemy[3][j].delay--;
                    }
                    else
                    {
                        enemy[3][j].guns_delay--;
                    }
                    enemy[3][j].isStanding=false;
                    for (int i=-enemy[3][j].width; i<=enemy[3][j].width; i++)
                    {
                        if (mp.M[round1(enemy[3][j].position.pos.x)+i][round1(enemy[3][j].position.pos.y)+enemy[3][j].height+1]>0)
                        {
                            enemy[3][j].isStanding=true;
                            break;
                        }
                    }
                    if (enemy[3][j].isStanding)
                    {
                        if (enemy[3][j].jump_counter>0)
                        {
                            enemy[3][j].jump_counter--;
                        }



                        if (enemy[3][j].position.speed.x>0)
                {
                    if (enemy[3][j].pos_x>0)
                    {
                        enemy[3][j].body.step(enemy[3][j].position.speed.x*(0.16/enemy[3][j].max_speed));
                    }
                    else
                    {
                        enemy[3][j].body.step(-enemy[3][j].position.speed.x*(0.16/enemy[3][j].max_speed));
                    }
                    if (enemy[3][j].position.speed.x>friction)
                    {
                        enemy[3][j].position.speed.x-=friction;
                    }
                else
                {
                    enemy[3][j].position.speed.x=0;
                }
            }
            else if (enemy[3][j].position.speed.x<0)
            {
                if (enemy[3][j].pos_x<0)
                    {
                        enemy[3][j].body.step(enemy[3][j].position.speed.x*(0.16/enemy[3][j].max_speed));
                    }
                    else
                    {
                        enemy[3][j].body.step(-enemy[3][j].position.speed.x*(0.16/enemy[3][j].max_speed));
                    }
                if (enemy[3][j].position.speed.x<-friction)
                {
                    enemy[3][j].position.speed.x+=friction;
                }
                else
                {
                    enemy[3][j].position.speed.x=0;
                }
            }

                    int a1=round1(enemy[3][j].position.pos.x);
                    int c=round1(enemy[3][j].position.pos.y);
                    for (int i=c-enemy[3][j].head_height; i<c+enemy[3][j].height; i++)
                {
                    if ((mp.M[a1+enemy[3][j].width+1][i]==1||mp.M[a1-enemy[3][j].width-1][i]==1)&&enemy[3][j].jump_counter<=0)
                    {
                        enemy[3][j].position.speed.y-=enemy[3][j].jump_force;
                        enemy[3][j].jump_counter=30;
                        break;
                    }
                }
                if (abs(enemy[3][j].position.speed.x)<0.1)
                        {
                            enemy[3][j].body.sprite.setTexture(enemy[3][j].idle);
                            enemy[3][j].body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
                            enemy[3][j].body.pos=0.1;
                        }

                    }
                    else
                    {


                            enemy[3][j].body.sprite.setTexture(enemy[3][j].jump);
                            enemy[3][j].body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
                            enemy[3][j].body.pos=0.1;



                    }



                    if (enemy[3][j].position.pos.x>player.position.pos.x+100)
                    {
                        if (enemy[3][j].guns_delay==enemy[3][j].max_guns_delay)
                        {
                            if (mp.M[round1(enemy[3][j].position.pos.x)][round1(enemy[3][j].position.pos.y)+enemy[3][j].height+1]==1)
                            {
                                enemy[3][j].position.speed.x-=enemy[3][j].strafe_force;
                                //enemy[0][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[3][j].position.speed.x-=enemy[3][j].air_strafe_force;
                                //enemy[0][j].body_frame_counter=0;
                            }
                        }
                    }
                    else if (enemy[3][j].position.pos.x<player.position.pos.x-100)
                    {
                    if (enemy[3][j].guns_delay==enemy[3][j].max_guns_delay)
                        {
                            if (mp.M[round1(enemy[3][j].position.pos.x)][round1(enemy[3][j].position.pos.y)+enemy[3][j].height+1]==1)
                            {
                                enemy[3][j].position.speed.x+=enemy[3][j].strafe_force;
                                //enemy[0][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[3][j].position.speed.x+=enemy[3][j].air_strafe_force;
                                //enemy[0][j].body_frame_counter=0;
                            }
                        }
                    }

                if (enemy[3][j].position.speed.x<-10&&enemy[3][j].isStanding)
                {
                        enemy[3][j].position.speed.x=-10;
                }

                if (enemy[3][j].position.speed.x>10&&enemy[3][j].isStanding)
                {
                        enemy[3][j].position.speed.x=10;
                }



                if (enemy[3][j].guns_delay==0)
                {
                    enemy[3][j].animation_delay=guns[enemy[3][j].gun_holding].max_delay;

                    enemy[3][j].weapon_sound.play();
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    bullet=enemy_shoot(player.position.pos.x, player.position.pos.y, player.head_height, player.height, player.width, rotation(enemy[3][j].pos_x, enemy[3][j].pos_y), enemy[3][j].position.pos.x, enemy[3][j].position.pos.y, guns[enemy[3][j].gun_holding].damage, guns[enemy[3][j].gun_holding].max_distance, mp);
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    if (bullet.hit)
                    {
                        player.health-=bullet.damage;
                        player.position.speed.x+=cos(rotation(bullet.final_x-enemy[3][j].position.pos.x, bullet.final_y-enemy[3][j].position.pos.y))*guns[enemy[3][j].gun_holding].knockback;
                        player.position.speed.y+=sin(rotation(bullet.final_x-enemy[3][j].position.pos.x, bullet.final_y-enemy[3][j].position.pos.y))*guns[enemy[3][j].gun_holding].knockback;
                    }
                    enemy[3][j].bullet.setPosition(960-player.position.pos.x+enemy[3][j].position.pos.x, 540-player.position.pos.y+enemy[3][j].position.pos.y);
                    enemy[3][j].bullet.setScale(bullet.distance, sign1(enemy[3][j].pos_x));
                    enemy[3][j].bullet.setRotation(rotation(enemy[3][j].pos_x, enemy[3][j].pos_y)*57);
                    window.draw(enemy[3][j].bullet);
                    enemy[3][j].guns_delay=enemy[3][j].max_guns_delay;
                    enemy[3][j].delay=enemy[3][j].max_delay;
                }
                enemy[3][j].body.setPR(sign1(enemy[3][j].pos_x), 960+enemy[3][j].position.pos.x-player.position.pos.x, 540+enemy[3][j].position.pos.y-player.position.pos.y, 0);

                enemy[3][j].head.setPR(sign1(enemy[3][j].pos_x), 960+enemy[3][j].position.pos.x-player.position.pos.x, 540+enemy[3][j].position.pos.y-player.position.pos.y, rt(enemy[3][j].pos_x, enemy[3][j].pos_y));

                guns[enemy[3][j].gun_holding].animation.setPR(sign1(enemy[3][j].pos_x), 960+enemy[3][j].position.pos.x-player.position.pos.x, 540+enemy[3][j].position.pos.y-player.position.pos.y, rt(enemy[3][j].pos_x, enemy[3][j].pos_y));

                enemy[3][j].left.setPR(sign1(enemy[3][j].pos_x), 960+enemy[3][j].position.pos.x-player.position.pos.x, 540+enemy[3][j].position.pos.y-player.position.pos.y, rt(enemy[3][j].pos_x, enemy[3][j].pos_y));
                enemy[3][j].right.setPR(sign1(enemy[3][j].pos_x), 960+enemy[3][j].position.pos.x-player.position.pos.x, 540+enemy[3][j].position.pos.y-player.position.pos.y, rt(enemy[3][j].pos_x, enemy[3][j].pos_y));


                    guns[enemy[3][j].gun_holding].animation.setFrame(enemy[3][j].animation_delay);
                    enemy[3][j].left.setFrame(enemy[3][j].animation_delay);
                    enemy[3][j].right.setFrame(enemy[3][j].animation_delay);













                window.draw(enemy[3][j].left.sprite);

                window.draw(guns[enemy[3][j].gun_holding].animation.sprite);


                window.draw(enemy[3][j].body.sprite);

                window.draw(enemy[3][j].head.sprite);







                window.draw(enemy[3][j].right.sprite);


                enemy_health.setPosition(enemy[3][j].position.pos.x-player.position.pos.x+860, enemy[3][j].position.pos.y-player.position.pos.y+440);
                health1=enemy[3][j].health;
                enemy_health.setScale((200*health1/enemy[3][j].max_health), 1);
                window.draw(enemy_health);




            }
            else
            {
                enemy[3][j].delay=enemy[3][j].max_delay;
            }


                    //enemy[0][j].position=engine(enemy[0][j].position, enemy[0][j].head_height, enemy[0][j].height);



                if (enemy[3][j].animation_delay)
                {
                    enemy[3][j].animation_delay--;
                }



                enemy[3][j].position.engine(enemy[3][j].head_height, enemy[3][j].height, enemy[3][j].width, mp);






                if (enemy[3][j].position.speed.x>enemy[3][j].max_speed&&enemy[3][j].isStanding)
                {
                    enemy[3][j].position.speed.x=enemy[3][j].max_speed;
                }
                else if (enemy[3][j].position.speed.x<-enemy[3][j].max_speed&&enemy[3][j].isStanding)
                {
                    enemy[3][j].position.speed.x=-enemy[3][j].max_speed;
                }

            }
            }
                /*


            if (enemy[3][j].health>0)
                {
                if (abs(enemy[3][j].position.x-player.position.x)<=enemy[3][j].sight_x&&abs(enemy[3][j].position.y-player.position.y)<=enemy[3][j].sight_y)
                {
                    if (enemy[3][j].delay)
                    {
                        enemy[3][j].guns_delay=enemy[3][j].max_guns_delay;
                        enemy[3][j].pos_x=player.position.x-enemy[3][j].position.x;
                        enemy[3][j].pos_y=player.position.y-enemy[3][j].position.y;
                        enemy[3][j].delay--;
                    }
                    else
                    {
                        enemy[3][j].guns_delay--;
                    }
                    bool isStanding=false;
                    for (int i=-enemy[3][j].width; i<=enemy[3][j].width; i++)
                    {
                        if (map0[round1(enemy[3][j].position.x)+i][round1(enemy[3][j].position.y)+enemy[3][j].height+1]>0)
                        {
                            isStanding=true;
                            break;
                        }
                    }
                    if (isStanding)
                    {
                        enemy[3][j].body1.setTextureRect(IntRect(enemy[3][j].body_sprite_positionx[enemy[3][j].body_frame_counter], 0, 99, 99));
                        enemy[3][j].body4.setTextureRect(IntRect(enemy[3][j].body_sprite_positionx[enemy[3][j].body_frame_counter], 0, 99, 99));

                        if (enemy[3][j].position.speed_x>0)
            {
                if (enemy[3][j].position.speed_x>friction)
                {
                    enemy[3][j].position.speed_x-=friction;
                }
                else
                {Keyboard::R
                    enemy[3][j].position.speed_x=0;
                }
            }
            else if (enemy[3][j].position.speed_x<0)
            {
                if (enemy[3][j].position.speed_x<-friction)
                {
                    enemy[3][j].position.speed_x+=friction;
                }
                else
                {
                    enemy[3][j].position.speed_x=0;
                }
            }

            int a1=round1(enemy[3][j].position.x);
                    int c=round1(enemy[3][j].position.y);
                    for (int i=c-enemy[3][j].head_height; i<c+enemy[3][j].height; i++)
                {
                    if ((map0[a1+enemy[3][j].width+1][i]==1||map0[a1-enemy[3][j].width-1][i]==1))
                    {
                        enemy[3][j].position.speed_y-=enemy[3][j].jump_force;
                        break;
                    }
                }
                    }
                    else
                    {
                        enemy[3][j].body1.setTextureRect(IntRect(300, 0, 100, 100));
                        enemy[3][j].body4.setTextureRect(IntRect(300, 0, 100, 100));
                    }
                    if (enemy[3][j].position.x>player.position.x+100)
                    {
                        if (enemy[3][j].guns_delay==enemy[3][j].max_guns_delay)
                        {
                            if (map0[round1(enemy[3][j].position.x)][round1(enemy[3][j].position.y)+enemy[3][j].height+1]==1)
                            {
                                enemy[3][j].position.speed_x-=enemy[3][j].strafe_force;
                                enemy[3][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[3][j].position.speed_x-=enemy[3][j].air_strafe_force;
                                enemy[3][j].body_frame_counter=0;
                            }
                        }
                    }
                    else if (enemy[3][j].position.x<player.position.x-100)
                    {
                    if (enemy[3][j].guns_delay==enemy[3][j].max_guns_delay)
                        {
                            if (map0[round1(enemy[3][j].position.x)][round1(enemy[3][j].position.y)+enemy[3][j].height+1]==1)
                            {
                                enemy[3][j].position.speed_x+=enemy[3][j].strafe_force;
                                enemy[3][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[3][j].position.speed_x+=enemy[3][j].air_strafe_force;
                                enemy[3][j].body_frame_counter=0;
                            }
                        }

                    }

                if (enemy[3][j].position.speed_x<-10)
                {
                        enemy[3][j].position.speed_x=-10;
                }

                if (enemy[3][j].position.speed_x>10)
                {
                        enemy[3][j].position.speed_x=10;
                }
                if (enemy[3][j].body_frame_counter>=29)
                {
                    enemy[3][j].body_frame_counter=0;
                }
                else if (enemy[3][j].body_frame_counter<1)
                {
                    enemy[3][j].body_frame_counter=29;
                }
                if ((enemy[3][j].position.x>=player.position.x-100&&enemy[3][j].position.x<=player.position.x+100)||enemy[3][j].delay==0)
                {
                    enemy[3][j].body_frame_counter=0;
                }

                 if (enemy[3][j].guns_delay==0)
                {
                    enemy[3][j].animation_delay=guns[enemy[3][j].gun_holding].max_delay;

                    enemy[3][j].weapon_sound.play();
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    bullet=enemy_shoot(player.position.x, player.position.y, player.head_height, player.height, player.width, rotation(enemy[3][j].pos_x, enemy[3][j].pos_y), enemy[3][j].position.x, enemy[3][j].position.y, guns[enemy[3][j].gun_holding].damage, guns[enemy[3][j].gun_holding].max_distance);
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    if (bullet.hit)
                    {
                        player.health-=bullet.damage;
                    }
                    enemy[3][j].bullet.setPosition(960-player.position.x+enemy[3][j].position.x, 540-player.position.y+enemy[3][j].position.y);
                    enemy[3][j].bullet.setScale(bullet.distance, -1);
                    enemy[3][j].bullet.setRotation(rotation(enemy[3][j].pos_x, enemy[3][j].pos_y)*57);
                    window.draw(enemy[3][j].bullet);
                    enemy[3][j].guns_delay=enemy[3][j].max_guns_delay;
                    enemy[3][j].delay=enemy[3][j].max_delay;
                }
                enemy[3][j].body1.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                enemy[3][j].body4.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                enemy[3][j].head2.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                enemy[3][j].head3.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);

                guns[enemy[3][j].gun_holding].sprite1.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                guns[enemy[3][j].gun_holding].sprite2.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                guns[enemy[3][j].gun_holding].sprite3.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                guns[enemy[3][j].gun_holding].sprite4.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                enemy[3][j].hands[enemy[3][j].gun_holding].left1.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                enemy[3][j].hands[enemy[3][j].gun_holding].left2.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                enemy[3][j].hands[enemy[3][j].gun_holding].left3.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                enemy[3][j].hands[enemy[3][j].gun_holding].left4.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                enemy[3][j].hands[enemy[3][j].gun_holding].right1.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                enemy[3][j].hands[enemy[3][j].gun_holding].right2.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                enemy[3][j].hands[enemy[3][j].gun_holding].right3.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);
                enemy[3][j].hands[enemy[3][j].gun_holding].right4.setPosition(960+enemy[3][j].position.x-player.position.x, 540+enemy[3][j].position.y-player.position.y);



                    enemy[3][j].head1.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y));
                    enemy[3][j].head2.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y)+270);
                    enemy[3][j].head3.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y)+180);
                    enemy[3][j].head4.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y)+90);

                    guns[enemy[3][j].gun_holding].sprite1.setTextureRect(IntRect(guns[enemy[3][j].gun_holding].positionx[enemy[3][j].animation_delay], 0, guns[enemy[3][j].gun_holding].width, guns[enemy[3][j].gun_holding].height));
                    guns[enemy[3][j].gun_holding].sprite2.setTextureRect(IntRect(guns[enemy[3][j].gun_holding].positionx[enemy[3][j].animation_delay], 0, guns[enemy[3][j].gun_holding].width, guns[enemy[3][j].gun_holding].height));
                    guns[enemy[3][j].gun_holding].sprite3.setTextureRect(IntRect(guns[enemy[3][j].gun_holding].positionx[enemy[3][j].animation_delay], 0, guns[enemy[3][j].gun_holding].width, guns[enemy[3][j].gun_holding].height));
                    guns[enemy[3][j].gun_holding].sprite4.setTextureRect(IntRect(guns[enemy[3][j].gun_holding].positionx[enemy[3][j].animation_delay], 0, guns[enemy[3][j].gun_holding].width, guns[enemy[3][j].gun_holding].height));

                    guns[enemy[3][j].gun_holding].sprite1.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y));
                    guns[enemy[3][j].gun_holding].sprite2.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y)+270);
                    guns[enemy[3][j].gun_holding].sprite3.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y)+180);
                    guns[enemy[3][j].gun_holding].sprite4.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y)+90);

                    enemy[3][j].hands[enemy[3][j].gun_holding].left1.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y));
                    enemy[3][j].hands[enemy[3][j].gun_holding].left2.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y)+270);
                    enemy[3][j].hands[enemy[3][j].gun_holding].left3.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y)+180);
                    enemy[3][j].hands[enemy[3][j].gun_holding].left4.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y)+90);

                    if (guns[enemy[3][j].gun_holding].isPistol)
                    {
                        enemy[3][j].hands[enemy[3][j].gun_holding].right1.setRotation(0);
                        enemy[3][j].hands[enemy[3][j].gun_holding].right2.setRotation(270);
                        enemy[3][j].hands[enemy[3][j].gun_holding].right3.setRotation(180);
                        enemy[3][j].hands[enemy[3][j].gun_holding].right4.setRotation(90);
                    }
                    else
                    {
                        enemy[3][j].hands[enemy[3][j].gun_holding].right1.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y));
                        enemy[3][j].hands[enemy[3][j].gun_holding].right2.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y)+270);
                        enemy[3][j].hands[enemy[3][j].gun_holding].right3.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y)+180);
                        enemy[3][j].hands[enemy[3][j].gun_holding].right4.setRotation(rt(enemy[3][j].pos_x, enemy[3][j].pos_y)+90);
                    }



                        int a=sign1(enemy[3][j].pos_x);


                        enemy[3][j].body1.setScale(a, 1);
                        enemy[3][j].body4.setScale(1, a);
                        enemy[3][j].head2.setScale(1, a);
                        enemy[3][j].head3.setScale(a, 1);

                        guns[enemy[3][j].gun_holding].sprite1.setScale(a, 1);
                        guns[enemy[3][j].gun_holding].sprite2.setScale(1, a);
                        guns[enemy[3][j].gun_holding].sprite3.setScale(a, 1);
                        guns[enemy[3][j].gun_holding].sprite4.setScale(1, a);

                        enemy[3][j].hands[enemy[3][j].gun_holding].left1.setScale(a, 1);
                        enemy[3][j].hands[enemy[3][j].gun_holding].left2.setScale(1, a);
                        enemy[3][j].hands[enemy[3][j].gun_holding].left3.setScale(a, 1);
                        enemy[3][j].hands[enemy[3][j].gun_holding].left4.setScale(1, a);

                        enemy[3][j].hands[enemy[3][j].gun_holding].right1.setScale(a, 1);
                        enemy[3][j].hands[enemy[3][j].gun_holding].right2.setScale(1, a);
                        enemy[3][j].hands[enemy[3][j].gun_holding].right3.setScale(a, 1);
                        enemy[3][j].hands[enemy[3][j].gun_holding].right4.setScale(1, a);









                window.draw(enemy[3][j].hands[enemy[3][j].gun_holding].left1);
                window.draw(enemy[3][j].hands[enemy[3][j].gun_holding].left2);
                window.draw(enemy[3][j].hands[enemy[3][j].gun_holding].left3);
                window.draw(enemy[3][j].hands[enemy[3][j].gun_holding].left4);

                window.draw(enemy[3][j].body1);
                window.draw(enemy[3][j].body4);
                window.draw(enemy[3][j].head2);
                window.draw(enemy[3][j].head3);



                window.draw(guns[enemy[3][j].gun_holding].sprite1);
                window.draw(guns[enemy[3][j].gun_holding].sprite2);
                window.draw(guns[enemy[3][j].gun_holding].sprite3);
                window.draw(guns[enemy[3][j].gun_holding].sprite4);

                window.draw(enemy[3][j].hands[enemy[3][j].gun_holding].right1);
                window.draw(enemy[3][j].hands[enemy[3][j].gun_holding].right2);
                window.draw(enemy[3][j].hands[enemy[3][j].gun_holding].right3);
                window.draw(enemy[3][j].hands[enemy[3][j].gun_holding].right4);

                enemy_health.setPosition(enemy[3][j].position.x-player.position.x+860, enemy[3][j].position.y-player.position.y+440);
                health1=enemy[3][j].health;
                enemy_health.setScale((200*health1/enemy[3][j].max_health), 1);
                window.draw(enemy_health);




            }
            else
            {
                enemy[3][j].delay=enemy[3][j].max_delay;
            }


                    //enemy[0][j].position=engine(enemy[0][j].position, enemy[0][j].head_height, enemy[0][j].height);



                if (enemy[3][j].animation_delay)
                {
                    enemy[3][j].animation_delay--;
                }



                enemy[3][j].position=engine(enemy[3][j].position, enemy[3][j].head_height, enemy[3][j].height, enemy[3][j].width);








                if (enemy[3][j].position.speed_x>enemy[3][j].max_speed)
                {
                    enemy[3][j].position.speed_x=enemy[3][j].max_speed;
                }
                else if (enemy[3][j].position.speed_x<-enemy[3][j].max_speed)
                {
                    enemy[3][j].position.speed_x=-enemy[3][j].max_speed;
                }

            }
            }
            for (int j=0; j<enemy[4][0].quantity; j++)
            {


            if (enemy[4][j].health>0)
                {
                if (abs(enemy[4][j].position.x-player.position.x)<=enemy[4][j].sight_x&&abs(enemy[4][j].position.y-player.position.y)<=enemy[4][j].sight_y)
                {
                    if (enemy[4][j].delay)
                    {
                        enemy[4][j].guns_delay=enemy[4][j].max_guns_delay;
                        enemy[4][j].pos_x=player.position.x-enemy[4][j].position.x;
                        enemy[4][j].pos_y=player.position.y-enemy[4][j].position.y;
                        enemy[4][j].delay--;
                    }
                    else
                    {
                        enemy[4][j].guns_delay--;
                    }
                    bool isStanding=false;
                    for (int i=-enemy[4][j].width; i<=enemy[4][j].width; i++)
                    {
                        if (map0[round1(enemy[4][j].position.x)+i][round1(enemy[4][j].position.y)+enemy[4][j].height+1]>0)
                        {
                            isStanding=true;
                            break;
                        }
                    }
                    if (isStanding)
                    {
                        enemy[4][j].body1.setTextureRect(IntRect(enemy[4][j].body_sprite_positionx[enemy[4][j].body_frame_counter], 0, 99, 99));
                        enemy[4][j].body4.setTextureRect(IntRect(enemy[4][j].body_sprite_positionx[enemy[4][j].body_frame_counter], 0, 99, 99));

                        if (enemy[4][j].position.speed_x>0)
            {
                if (enemy[4][j].position.speed_x>friction)
                {
                    enemy[4][j].position.speed_x-=friction;
                }
                else
                {
                    enemy[4][j].position.speed_x=0;
                }
            }
            else if (enemy[4][j].position.speed_x<0)
            {
                if (enemy[4][j].position.speed_x<-friction)
                {
                    enemy[4][j].position.speed_x+=friction;
                }
                else
                {
                    enemy[4][j].position.speed_x=0;
                }
            }

            int a1=round1(enemy[4][j].position.x);
                    int c=round1(enemy[4][j].position.y);
                    for (int i=c-enemy[4][j].head_height; i<c+enemy[4][j].height; i++)
                {
                    if ((map0[a1+enemy[4][j].width+1][i]==1||map0[a1-enemy[4][j].width-1][i]==1))
                    {
                        enemy[4][j].position.speed_y-=enemy[4][j].jump_force;
                        break;
                    }
                }
                    }
                    else
                    {
                        enemy[4][j].body1.setTextureRect(IntRect(300, 0, 100, 100));
                        enemy[4][j].body4.setTextureRect(IntRect(300, 0, 100, 100));
                    }
                    if (enemy[4][j].position.x>player.position.x+100)
                    {
                        if (enemy[4][j].guns_delay==enemy[4][j].max_guns_delay)
                        {
                            if (map0[round1(enemy[4][j].position.x)][round1(enemy[4][j].position.y)+enemy[4][j].height+1]==1)
                            {
                                enemy[4][j].position.speed_x-=enemy[4][j].strafe_force;
                                enemy[4][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[4][j].position.speed_x-=enemy[4][j].air_strafe_force;
                                enemy[4][j].body_frame_counter=0;
                            }
                        }
                    }
                    else if (enemy[4][j].position.x<player.position.x-100)
                    {
                    if (enemy[4][j].guns_delay==enemy[4][j].max_guns_delay)
                        {
                            if (map0[round1(enemy[4][j].position.x)][round1(enemy[4][j].position.y)+enemy[4][j].height+1]==1)
                            {
                                enemy[4][j].position.speed_x+=enemy[4][j].strafe_force;
                                enemy[4][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[4][j].position.speed_x+=enemy[4][j].air_strafe_force;
                                enemy[4][j].body_frame_counter=0;
                            }
                        }

                    }

                if (enemy[4][j].position.speed_x<-10)
                {
                        enemy[4][j].position.speed_x=-10;
                }

                if (enemy[4][j].position.speed_x>10)
                {
                        enemy[4][j].position.speed_x=10;
                }

                if (enemy[4][j].body_frame_counter>=29)
                {
                    enemy[4][j].body_frame_counter=0;
                }
                else if (enemy[4][j].body_frame_counter<1)
                {
                    enemy[4][j].body_frame_counter=29;
                }
                if ((enemy[4][j].position.x>=player.position.x-100&&enemy[4][j].position.x<=player.position.x+100)||enemy[4][j].delay==0)
                {
                    enemy[4][j].body_frame_counter=0;
                }
                 if (enemy[4][j].guns_delay==0)
                {
                    enemy[4][j].animation_delay=guns[enemy[4][j].gun_holding].max_delay;

                    enemy[4][j].weapon_sound.play();
                    for (int i=1; i<=guns[enemy[4][j].gun_holding].pellets; i++)
                    {
                        bullet=enemy_shoot(player.position.x, player.position.y, player.head_height, player.height, player.width, rotation(enemy[4][j].pos_x, enemy[4][j].pos_y)+i*guns[enemy[4][j].gun_holding].pellet_spread, enemy[4][j].position.x, enemy[4][j].position.y, guns[enemy[4][j].gun_holding].damage, guns[enemy[4][j].gun_holding].max_distance);
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    if (bullet.hit)
                    {
                        player.health-=bullet.damage;
                    }
                    enemy[4][j].bullet.setPosition(960-player.position.x+enemy[4][j].position.x, 540-player.position.y+enemy[4][j].position.y);
                    enemy[4][j].bullet.setScale(bullet.distance, 1);
                    enemy[4][j].bullet.setRotation(rotation(enemy[4][j].pos_x, enemy[4][j].pos_y)*57+i*guns[enemy[4][j].gun_holding].pellet_spread*57);
                    window.draw(enemy[4][j].bullet);


                    bullet=enemy_shoot(player.position.x, player.position.y, player.head_height, player.height, player.width, rotation(enemy[4][j].pos_x, enemy[4][j].pos_y)-i*guns[enemy[4][j].gun_holding].pellet_spread, enemy[4][j].position.x, enemy[4][j].position.y, guns[enemy[4][j].gun_holding].damage, guns[enemy[4][j].gun_holding].max_distance);
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    if (bullet.hit)
                    {
                        player.health-=bullet.damage;
                    }
                    enemy[4][j].bullet.setPosition(960-player.position.x+enemy[4][j].position.x, 540-player.position.y+enemy[4][j].position.y);
                    enemy[4][j].bullet.setScale(bullet.distance, 1);
                    enemy[4][j].bullet.setRotation(rotation(enemy[4][j].pos_x, enemy[4][j].pos_y)*57-i*guns[enemy[4][j].gun_holding].pellet_spread*57);
                    window.draw(enemy[4][j].bullet);


                    }
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    bullet=enemy_shoot(player.position.x, player.position.y, player.head_height, player.height, player.width, rotation(enemy[4][j].pos_x, enemy[4][j].pos_y), enemy[4][j].position.x, enemy[4][j].position.y, guns[enemy[4][j].gun_holding].damage, guns[enemy[4][j].gun_holding].max_distance);
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    if (bullet.hit)
                    {
                        player.health-=bullet.damage;
                    }
                    enemy[4][j].bullet.setPosition(960-player.position.x+enemy[4][j].position.x, 540-player.position.y+enemy[4][j].position.y);
                    enemy[4][j].bullet.setScale(bullet.distance, 1);
                    enemy[4][j].bullet.setRotation(rotation(enemy[4][j].pos_x, enemy[4][j].pos_y)*57);
                    window.draw(enemy[4][j].bullet);
                    enemy[4][j].guns_delay=enemy[4][j].max_guns_delay;
                    enemy[4][j].delay=enemy[4][j].max_delay;
                }
                enemy[4][j].body1.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                enemy[4][j].body4.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                enemy[4][j].head2.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                enemy[4][j].head3.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);

                guns[enemy[4][j].gun_holding].sprite1.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                guns[enemy[4][j].gun_holding].sprite2.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                guns[enemy[4][j].gun_holding].sprite3.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                guns[enemy[4][j].gun_holding].sprite4.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                enemy[4][j].hands[enemy[4][j].gun_holding].left1.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                enemy[4][j].hands[enemy[4][j].gun_holding].left2.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                enemy[4][j].hands[enemy[4][j].gun_holding].left3.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                enemy[4][j].hands[enemy[4][j].gun_holding].left4.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                enemy[4][j].hands[enemy[4][j].gun_holding].right1.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                enemy[4][j].hands[enemy[4][j].gun_holding].right2.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                enemy[4][j].hands[enemy[4][j].gun_holding].right3.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);
                enemy[4][j].hands[enemy[4][j].gun_holding].right4.setPosition(960+enemy[4][j].position.x-player.position.x, 540+enemy[4][j].position.y-player.position.y);



                    enemy[4][j].head1.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y));
                    enemy[4][j].head2.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y)+270);
                    enemy[4][j].head3.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y)+180);
                    enemy[4][j].head4.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y)+90);

                    guns[enemy[4][j].gun_holding].sprite1.setTextureRect(IntRect(guns[enemy[4][j].gun_holding].positionx[enemy[4][j].animation_delay], 0, guns[enemy[4][j].gun_holding].width, guns[enemy[4][j].gun_holding].height));
                    guns[enemy[4][j].gun_holding].sprite2.setTextureRect(IntRect(guns[enemy[4][j].gun_holding].positionx[enemy[4][j].animation_delay], 0, guns[enemy[4][j].gun_holding].width, guns[enemy[4][j].gun_holding].height));
                    guns[enemy[4][j].gun_holding].sprite3.setTextureRect(IntRect(guns[enemy[4][j].gun_holding].positionx[enemy[4][j].animation_delay], 0, guns[enemy[4][j].gun_holding].width, guns[enemy[4][j].gun_holding].height));
                    guns[enemy[4][j].gun_holding].sprite4.setTextureRect(IntRect(guns[enemy[4][j].gun_holding].positionx[enemy[4][j].animation_delay], 0, guns[enemy[4][j].gun_holding].width, guns[enemy[4][j].gun_holding].height));

                    guns[enemy[4][j].gun_holding].sprite1.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y));
                    guns[enemy[4][j].gun_holding].sprite2.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y)+270);
                    guns[enemy[4][j].gun_holding].sprite3.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y)+180);
                    guns[enemy[4][j].gun_holding].sprite4.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y)+90);

                    enemy[4][j].hands[enemy[4][j].gun_holding].left1.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y));
                    enemy[4][j].hands[enemy[4][j].gun_holding].left2.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y)+270);
                    enemy[4][j].hands[enemy[4][j].gun_holding].left3.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y)+180);
                    enemy[4][j].hands[enemy[4][j].gun_holding].left4.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y)+90);

                    if (guns[enemy[4][j].gun_holding].isPistol)
                    {
                        enemy[4][j].hands[enemy[4][j].gun_holding].right1.setRotation(0);
                        enemy[4][j].hands[enemy[4][j].gun_holding].right2.setRotation(270);
                        enemy[4][j].hands[enemy[4][j].gun_holding].right3.setRotation(180);
                        enemy[4][j].hands[enemy[4][j].gun_holding].right4.setRotation(90);
                    }
                    else
                    {
                        enemy[4][j].hands[enemy[4][j].gun_holding].right1.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y));
                        enemy[4][j].hands[enemy[4][j].gun_holding].right2.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y)+270);
                        enemy[4][j].hands[enemy[4][j].gun_holding].right3.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y)+180);
                        enemy[4][j].hands[enemy[4][j].gun_holding].right4.setRotation(rt(enemy[4][j].pos_x, enemy[4][j].pos_y)+90);
                    }

                        enemy[4][j].hands[enemy[4][j].gun_holding].right1.setTextureRect(IntRect(guns[enemy[4][j].gun_holding].right_positionx[enemy[4][j].animation_delay], 0, 50, 50));
                        enemy[4][j].hands[enemy[4][j].gun_holding].right2.setTextureRect(IntRect(guns[enemy[4][j].gun_holding].right_positionx[enemy[4][j].animation_delay], 0, 50, 50));
                        enemy[4][j].hands[enemy[4][j].gun_holding].right3.setTextureRect(IntRect(guns[enemy[4][j].gun_holding].right_positionx[enemy[4][j].animation_delay], 0, 50, 50));
                        enemy[4][j].hands[enemy[4][j].gun_holding].right4.setTextureRect(IntRect(guns[enemy[4][j].gun_holding].right_positionx[enemy[4][j].animation_delay], 0, 50, 50));


                        int a=sign1(enemy[4][j].pos_x);


                        enemy[4][j].body1.setScale(a, 1);
                        enemy[4][j].body4.setScale(1, a);
                        enemy[4][j].head2.setScale(1, a);
                        enemy[4][j].head3.setScale(a, 1);

                        guns[enemy[4][j].gun_holding].sprite1.setScale(a, 1);
                        guns[enemy[4][j].gun_holding].sprite2.setScale(1, a);
                        guns[enemy[4][j].gun_holding].sprite3.setScale(a, 1);
                        guns[enemy[4][j].gun_holding].sprite4.setScale(1, a);

                        enemy[4][j].hands[enemy[4][j].gun_holding].left1.setScale(a, 1);
                        enemy[4][j].hands[enemy[4][j].gun_holding].left2.setScale(1, a);
                        enemy[4][j].hands[enemy[4][j].gun_holding].left3.setScale(a, 1);
                        enemy[4][j].hands[enemy[4][j].gun_holding].left4.setScale(1, a);

                        enemy[4][j].hands[enemy[4][j].gun_holding].right1.setScale(a, 1);
                        enemy[4][j].hands[enemy[4][j].gun_holding].right2.setScale(1, a);
                        enemy[4][j].hands[enemy[4][j].gun_holding].right3.setScale(a, 1);
                        enemy[4][j].hands[enemy[4][j].gun_holding].right4.setScale(1, a);









                window.draw(enemy[4][j].hands[enemy[4][j].gun_holding].left1);
                window.draw(enemy[4][j].hands[enemy[4][j].gun_holding].left2);
                window.draw(enemy[4][j].hands[enemy[4][j].gun_holding].left3);
                window.draw(enemy[4][j].hands[enemy[4][j].gun_holding].left4);

                window.draw(enemy[4][j].body1);
                window.draw(enemy[4][j].body4);
                window.draw(enemy[4][j].head2);
                window.draw(enemy[4][j].head3);



                window.draw(guns[enemy[4][j].gun_holding].sprite1);
                window.draw(guns[enemy[4][j].gun_holding].sprite2);
                window.draw(guns[enemy[4][j].gun_holding].sprite3);
                window.draw(guns[enemy[4][j].gun_holding].sprite4);

                window.draw(enemy[4][j].hands[enemy[4][j].gun_holding].right1);
                window.draw(enemy[4][j].hands[enemy[4][j].gun_holding].right2);
                window.draw(enemy[4][j].hands[enemy[4][j].gun_holding].right3);
                window.draw(enemy[4][j].hands[enemy[4][j].gun_holding].right4);

                enemy_health.setPosition(enemy[4][j].position.x-player.position.x+860, enemy[4][j].position.y-player.position.y+440);
                health1=enemy[4][j].health;
                enemy_health.setScale((200*health1/enemy[4][j].max_health), 1);
                window.draw(enemy_health);




            }
            else
            {
                enemy[4][j].delay=enemy[4][j].max_delay;
            }


                    //enemy[0][j].position=engine(enemy[0][j].position, enemy[0][j].head_height, enemy[0][j].height);



                if (enemy[4][j].animation_delay)
                {
                    enemy[4][j].animation_delay--;
                }



                enemy[4][j].position=engine(enemy[4][j].position, enemy[4][j].head_height, enemy[4][j].height, enemy[4][j].width);

                if (enemy[4][j].position.speed_x>enemy[4][j].max_speed)
                {
                    enemy[4][j].position.speed_x=enemy[4][j].max_speed;
                }
                else if (enemy[4][j].position.speed_x<-enemy[4][j].max_speed)
                {
                    enemy[4][j].position.speed_x=-enemy[4][j].max_speed;
                }

        }
            }*/

            /*bool isStanding=false;
        for (int i=-player.width; i<=player.width; i++)
        {
            if (map0[round1(player.position.x+i)][round1(player.position.y)+player.height+1]==1)
            {
            if (player.position.speed_x>0)
            {
                if (player.position.speed_x>friction)
                {
                    player.position.speed_x-=friction;
                }
                else
                {
                    player.position.speed_x=0;
                }
            }
            else if (player.position.speed_x<0)
            {
                if (player.position.speed_x<-friction)
                {
                    player.position.speed_x+=friction;
                }
                else
                {
                    player.position.speed_x=0;
                }
            }
            isStanding=true;
            break;
            }
        }*/
        for (int j=0; j<enemy[4][0].quantity; j++)
        {
            if (enemy[4][j].health>0)
                {
                    //std::cout << 1;
                    enemy[4][j].position.speed.y+=gravity;
                if (abs(enemy[4][j].position.pos.x-player.position.pos.x)<=enemy[4][j].sight_x&&abs(enemy[4][j].position.pos.y-player.position.pos.y)<=enemy[4][j].sight_y)
                {

                    if (enemy[4][j].delay)
                    {
                        enemy[4][j].guns_delay=enemy[4][j].max_guns_delay;
                        enemy[4][j].pos_x=player.position.pos.x-enemy[4][j].position.pos.x;
                        enemy[4][j].pos_y=player.position.pos.y-enemy[4][j].position.pos.y;
                        enemy[4][j].delay--;
                    }
                    else
                    {
                        enemy[4][j].guns_delay--;
                    }

                    enemy[4][j].isStanding=false;
                    for (int i=-enemy[4][j].width; i<=enemy[4][j].width; i++)
                    {
                        if (mp.M[round1(enemy[4][j].position.pos.x)+i][round1(enemy[4][j].position.pos.y)+enemy[4][j].height+1]>0)
                        {
                            enemy[4][j].isStanding=true;
                            break;
                        }
                    }//enemy[0][j].position.speed.yengine

                    if (enemy[4][j].isStanding)
                    {
                        if (enemy[4][j].jump_counter>0)
                        {
                            enemy[4][j].jump_counter--;
                        }



                        if (enemy[4][j].position.speed.x>0)
                {
                    if (enemy[4][j].pos_x>0)
                    {
                        enemy[4][j].body.step(enemy[4][j].position.speed.x*(0.16/enemy[4][j].max_speed));
                    }
                    else
                    {
                        enemy[4][j].body.step(-enemy[4][j].position.speed.x*(0.16/enemy[4][j].max_speed));
                    }
                    if (enemy[4][j].position.speed.x>friction)
                    {
                        enemy[4][j].position.speed.x-=friction;
                    }
                else
                {
                    enemy[4][j].position.speed.x=0;
                }
            }
            else if (enemy[4][j].position.speed.x<0)
            {
                if (enemy[4][j].pos_x<0)
                    {
                        enemy[4][j].body.step(enemy[4][j].position.speed.x*(0.16/enemy[4][j].max_speed));
                    }
                    else
                    {
                        enemy[4][j].body.step(-enemy[4][j].position.speed.x*(0.16/enemy[4][j].max_speed));
                    }
                if (enemy[4][j].position.speed.x<-friction)
                {
                    enemy[4][j].position.speed.x+=friction;
                }
                else//enemy[0
                {
                    enemy[4][j].position.speed.x=0;
                }
            }

                    int a1=round1(enemy[4][j].position.pos.x);
                    int c=round1(enemy[4][j].position.pos.y);
                    for (int i=c-enemy[4][j].head_height; i<c+enemy[4][j].height; i++)
                {
                    if ((mp.M[a1+enemy[4][j].width+1][i]==1||mp.M[a1-enemy[4][j].width-1][i]==1)&&enemy[4][j].jump_counter<=0)
                    {
                        enemy[4][j].position.speed.y-=enemy[4][j].jump_force;
                        enemy[4][j].jump_counter=30;
                        break;
                    }
                }
                if (abs(enemy[4][j].position.speed.x)<0.1)
                        {
                            enemy[4][j].body.sprite.setTexture(enemy[4][j].idle);
                            enemy[4][j].body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
                            enemy[4][j].body.pos=0.1;
                        }

                    }
                    else
                    {


                            enemy[4][j].body.sprite.setTexture(enemy[4][j].jump);
                            enemy[4][j].body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
                            enemy[4][j].body.pos=0.1;



                    }



                    if (enemy[4][j].position.pos.x>player.position.pos.x+100)
                    {
                        if (enemy[4][j].guns_delay==enemy[4][j].max_guns_delay)
                        {
                            if (mp.M[round1(enemy[4][j].position.pos.x)][round1(enemy[4][j].position.pos.y)+enemy[4][j].height+1]==1)
                            {
                                enemy[4][j].position.speed.x-=enemy[4][j].strafe_force;
                                //enemy[0][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[4][j].position.speed.x-=enemy[4][j].air_strafe_force;
                                //enemy[0][j].body_frame_counter=0;
                            }
                        }
                    }
                    else if (enemy[4][j].position.pos.x<player.position.pos.x-100)
                    {
                    if (enemy[4][j].guns_delay==enemy[4][j].max_guns_delay)
                        {
                            if (mp.M[round1(enemy[4][j].position.pos.x)][round1(enemy[4][j].position.pos.y)+enemy[4][j].height+1]==1)
                            {
                                enemy[4][j].position.speed.x+=enemy[4][j].strafe_force;
                                //enemy[0][j].body_frame_counter++;
                            }
                            else
                            {
                                enemy[4][j].position.speed.x+=enemy[4][j].air_strafe_force;
                                //enemy[0][j].body_frame_counter=0;
                            }
                        }
                    }

                if (enemy[4][j].position.speed.x<-10&&enemy[4][j].isStanding)
                {
                        enemy[4][j].position.speed.x=-10;
                }

                if (enemy[4][j].position.speed.x>10&&enemy[4][j].isStanding)
                {
                        enemy[4][j].position.speed.x=10;
                }




                if (enemy[4][j].guns_delay==0)
                {
                    enemy[4][j].animation_delay=110;

                    enemy[4][j].weapon_sound.play();
                    //std::cout << enemy[0][j].position.x << " " << enemy[0][j].position.y << std::endl;
                    bullet=enemy_shoot(player.position.pos.x, player.position.pos.y, player.head_height, player.height, player.width, rotation(enemy[4][j].pos_x, enemy[4][j].pos_y), enemy[4][j].position.pos.x, enemy[4][j].position.pos.y, guns[enemy[4][j].gun_holding].damage, guns[enemy[4][j].gun_holding].max_distance, mp);

                    enemy[4][j].position.speed.y-=guns[enemy[4][j].gun_holding].knockback*cos(rotation(enemy[4][j].pos_x, enemy[4][j].pos_y))*2;
                    enemy[4][j].position.speed.x-=guns[enemy[4][j].gun_holding].knockback*sin(rotation(enemy[4][j].pos_x, enemy[4][j].pos_y))*2;
                    if (bullet.hit)
                    {
                        player.health-=bullet.damage;
                        player.position.speed.x+=cos(rotation(bullet.final_x-enemy[4][j].position.pos.x, bullet.final_y-enemy[4][j].position.pos.y))*guns[enemy[4][j].gun_holding].knockback;
                        player.position.speed.y+=sin(rotation(bullet.final_x-enemy[4][j].position.pos.x, bullet.final_y-enemy[4][j].position.pos.y))*guns[enemy[4][j].gun_holding].knockback;
                    }
                    enemy[4][j].bullet.setPosition(960-player.position.pos.x+enemy[4][j].position.pos.x, 540-player.position.pos.y+enemy[4][j].position.pos.y);
                    enemy[4][j].bullet.setScale(bullet.distance, sign1(bullet.final_x-enemy[4][j].position.pos.x));
                    enemy[4][j].bullet.setRotation(rotation(bullet.final_x-enemy[4][j].position.pos.x, bullet.final_y-enemy[4][j].position.pos.y)*57);
                    window.draw(enemy[4][j].bullet);
                    enemy[4][j].guns_delay=enemy[4][j].max_guns_delay;
                    enemy[4][j].delay=enemy[4][j].max_delay;

                    for (int k=1; k<=4; k++)
                    {
                         bullet=enemy_shoot(player.position.pos.x, player.position.pos.y, player.head_height, player.height, player.width, rotation(enemy[4][j].pos_x, enemy[4][j].pos_y)+guns[enemy[4][j].gun_holding].pellet_spread*k, enemy[4][j].position.pos.x, enemy[4][j].position.pos.y, guns[enemy[4][j].gun_holding].damage, guns[enemy[4][j].gun_holding].max_distance, mp);

                    if (bullet.hit)
                    {
                        player.health-=bullet.damage;
                        player.position.speed.x+=cos(rotation(bullet.final_x-enemy[4][j].position.pos.x, bullet.final_y-enemy[4][j].position.pos.y))*guns[enemy[4][j].gun_holding].knockback;
                        player.position.speed.y+=sin(rotation(bullet.final_x-enemy[4][j].position.pos.x, bullet.final_y-enemy[4][j].position.pos.y))*guns[enemy[4][j].gun_holding].knockback;
                    }
                    enemy[4][j].bullet.setPosition(960-player.position.pos.x+enemy[4][j].position.pos.x, 540-player.position.pos.y+enemy[4][j].position.pos.y);
                    enemy[4][j].bullet.setScale(bullet.distance, sign1(bullet.final_x-enemy[4][j].position.pos.x));
                    enemy[4][j].bullet.setRotation(rotation(bullet.final_x-enemy[4][j].position.pos.x, bullet.final_y-enemy[4][j].position.pos.y)*57);
                    window.draw(enemy[4][j].bullet);
                    enemy[4][j].guns_delay=enemy[4][j].max_guns_delay;
                    enemy[4][j].delay=enemy[4][j].max_delay;




                     bullet=enemy_shoot(player.position.pos.x, player.position.pos.y, player.head_height, player.height, player.width, rotation(enemy[4][j].pos_x, enemy[4][j].pos_y)-guns[enemy[4][j].gun_holding].pellet_spread*k, enemy[4][j].position.pos.x, enemy[4][j].position.pos.y, guns[enemy[4][j].gun_holding].damage, guns[enemy[4][j].gun_holding].max_distance, mp);

                    if (bullet.hit)
                    {
                        player.health-=bullet.damage;
                        player.position.speed.x+=cos(rotation(bullet.final_x-enemy[4][j].position.pos.x, bullet.final_y-enemy[4][j].position.pos.y))*guns[enemy[4][j].gun_holding].knockback;
                        player.position.speed.y+=sin(rotation(bullet.final_x-enemy[4][j].position.pos.x, bullet.final_y-enemy[4][j].position.pos.y))*guns[enemy[4][j].gun_holding].knockback;
                    }
                    enemy[4][j].bullet.setPosition(960-player.position.pos.x+enemy[4][j].position.pos.x, 540-player.position.pos.y+enemy[4][j].position.pos.y);
                    enemy[4][j].bullet.setScale(bullet.distance, sign1(bullet.final_x-enemy[4][j].position.pos.x));
                    enemy[4][j].bullet.setRotation(rotation(bullet.final_x-enemy[4][j].position.pos.x, bullet.final_y-enemy[4][j].position.pos.y)*57);
                    window.draw(enemy[4][j].bullet);
                    enemy[4][j].guns_delay=enemy[4][j].max_guns_delay;
                    enemy[4][j].delay=enemy[4][j].max_delay;
                    }
                }




                    if (enemy[4][j].animation_delay==90)
                    {
                        enemy[4][j].reload_sound.play();
                    }

                    if (enemy[4][j].animation_delay>90)
                    {

                        enemy[4][j].body.setPR(sign1(enemy[4][j].pos_x), 960+enemy[4][j].position.pos.x-player.position.pos.x, 540+enemy[4][j].position.pos.y-player.position.pos.y, 0);

                enemy[4][j].head.setPR(sign1(enemy[4][j].pos_x), 960+enemy[4][j].position.pos.x-player.position.pos.x, 540+enemy[4][j].position.pos.y-player.position.pos.y, rt(enemy[4][j].pos_x, enemy[4][j].pos_y));

                guns[enemy[4][j].gun_holding].animation.setPR(sign1(enemy[4][j].pos_x), 960+enemy[4][j].position.pos.x-player.position.pos.x, 540+enemy[4][j].position.pos.y-player.position.pos.y, rt(enemy[4][j].pos_x, enemy[4][j].pos_y));

                enemy[4][j].left.setPR(sign1(enemy[4][j].pos_x), 960+enemy[4][j].position.pos.x-player.position.pos.x, 540+enemy[4][j].position.pos.y-player.position.pos.y, rt(enemy[4][j].pos_x, enemy[4][j].pos_y));
                enemy[4][j].right.setPR(sign1(enemy[4][j].pos_x), 960+enemy[4][j].position.pos.x-player.position.pos.x, 540+enemy[4][j].position.pos.y-player.position.pos.y, rt(enemy[4][j].pos_x, enemy[4][j].pos_y));

                        guns[enemy[4][j].gun_holding].animation.setFrame(enemy[4][j].animation_delay-90);
                    enemy[4][j].left.setFrame(enemy[4][j].animation_delay-90);
                    enemy[4][j].right.setFrame(enemy[4][j].animation_delay-90);

                    window.draw(enemy[4][j].left.sprite);

                window.draw(guns[enemy[4][j].gun_holding].animation.sprite);


                window.draw(enemy[4][j].body.sprite);

                window.draw(enemy[4][j].head.sprite);

                window.draw(enemy[4][j].right.sprite);
                    }
                    else
                    {

                        enemy[4][j].body.setPR(sign1(enemy[4][j].pos_x), 960+enemy[4][j].position.pos.x-player.position.pos.x, 540+enemy[4][j].position.pos.y-player.position.pos.y, 0);

                enemy[4][j].head.setPR(sign1(enemy[4][j].pos_x), 960+enemy[4][j].position.pos.x-player.position.pos.x, 540+enemy[4][j].position.pos.y-player.position.pos.y, rt(enemy[4][j].pos_x, enemy[4][j].pos_y));

                guns[enemy[4][j].gun_holding].reload.setPR(sign1(enemy[4][j].pos_x), 960+enemy[4][j].position.pos.x-player.position.pos.x, 540+enemy[4][j].position.pos.y-player.position.pos.y, rt(enemy[4][j].pos_x, enemy[4][j].pos_y));

                enemy[4][j].left_reload.setPR(sign1(enemy[4][j].pos_x), 960+enemy[4][j].position.pos.x-player.position.pos.x, 540+enemy[4][j].position.pos.y-player.position.pos.y, rt(enemy[4][j].pos_x, enemy[4][j].pos_y));
                enemy[4][j].right_reload.setPR(sign1(enemy[4][j].pos_x), 960+enemy[4][j].position.pos.x-player.position.pos.x, 540+enemy[4][j].position.pos.y-player.position.pos.y, rt(enemy[4][j].pos_x, enemy[4][j].pos_y));

                        guns[enemy[4][j].gun_holding].reload.setFrame(enemy[4][j].animation_delay);
                    enemy[4][j].left_reload.setFrame(enemy[4][j].animation_delay);
                    enemy[4][j].right_reload.setFrame(enemy[4][j].animation_delay);

                    window.draw(enemy[4][j].left_reload.sprite);

                window.draw(guns[enemy[4][j].gun_holding].reload.sprite);


                window.draw(enemy[4][j].body.sprite);

                window.draw(enemy[4][j].head.sprite);

                window.draw(enemy[4][j].right_reload.sprite);
                    }























                enemy_health.setPosition(enemy[4][j].position.pos.x-player.position.pos.x+860, enemy[4][j].position.pos.y-player.position.pos.y+440);
                health1=enemy[4][j].health;
                enemy_health.setScale((200*health1/enemy[4][j].max_health), 1);
                window.draw(enemy_health);




            }
            else
            {
                enemy[4][j].delay=enemy[4][j].max_delay;
            }


                    //enemy[0][j].position=engine(enemy[0][j].position, enemy[0][j].head_height, enemy[0][j].height);



                if (enemy[4][j].animation_delay)
                {
                    enemy[4][j].animation_delay--;
                }
                //std::cout << 2;




                enemy[4][j].position.engine(enemy[4][j].head_height, enemy[4][j].height, enemy[4][j].width, mp);

                //std::cout << 3;




                if (enemy[4][j].position.speed.x>enemy[4][j].max_speed&&enemy[4][j].isStanding)
                {
                    enemy[4][j].position.speed.x=enemy[4][j].max_speed;
                }
                else if (enemy[4][j].position.speed.x<-enemy[4][j].max_speed&&enemy[4][j].isStanding)
                {
                    enemy[4][j].position.speed.x=-enemy[4][j].max_speed;
                }

            }
        }
        if (player.deploy)
            {
                player.tilt=double(player.deploy)/57;
            }
        if (guns[player.gun_holding].predelay>0)
            {

                guns[player.gun_holding].predelay--;
                guns[player.gun_holding].pre.setFrame(guns[player.gun_holding].predelay);
                guns[player.gun_holding].left_pre.setFrame(guns[player.gun_holding].predelay);
                guns[player.gun_holding].right_pre.setFrame(guns[player.gun_holding].predelay);

                if (guns[player.gun_holding].predelay<1)
                {
                    //shoot player.slot_holding=
                    guns[player.gun_holding].sound.play();
                    player.play=true;
                    guns[player.gun_holding].ammo-=guns[player.gun_holding].ammo_used;

                    guns[player.gun_holding].delay=guns[player.gun_holding].max_delay;
                    double spread=random(guns[player.gun_holding].spread);
                    if (guns[player.gun_holding].isProjectile) // fire projectile(s)
                    {
                        int pr=-1;
                        for (int j=0; j<projectile_count; j++)
                        {
                            if (projectile[j].damage<=0&&projectile[j].time<=0)
                            {
                                pr=j;
                                break;
                            }
                        }
                        if (pr>=0)
                        {//launches a projectile
                            projectile[pr].multiplier=guns[player.gun_holding].splash_multiplier;
                            projectile[pr].animation=guns[player.gun_holding].projectile;
                            projectile[pr].time=guns[player.gun_holding].max_projectile_time;
                            projectile[pr].damage=guns[player.gun_holding].damage;
                            projectile[pr].speed=guns[player.gun_holding].proj_speed;
                            projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread;
                            projectile[pr].x=player.position.pos.x;
                            projectile[pr].y=player.position.pos.y;
                            projectile[pr].radius=guns[player.gun_holding].radius;
                            projectile[pr].distance_left=guns[player.gun_holding].max_distance;
                            projectile[pr].acceleration=guns[player.gun_holding].proj_acceleration;
                            projectile[pr].blast=guns[player.gun_holding].blast;
                            projectile[pr].blast.setPos(0.1);
                            projectile[pr].knockback=guns[player.gun_holding].knockback;
                            projectile[pr].gun=player.gun_holding;

                        }
                        for (int i=1; i<=guns[player.gun_holding].pellets; i++)
                        {
                            pr=-1;
                        for (int j=0; j<projectile_count; j++)
                        {
                            if (projectile[j].damage<=0&&projectile[j].time<=0)
                            {
                                pr=j;
                                break;
                            }
                        }
                        if (pr>=0)
                        {//launches a projectile
                            projectile[pr].multiplier=guns[player.gun_holding].splash_multiplier;
                            projectile[pr].animation=guns[player.gun_holding].projectile;
                            projectile[pr].time=guns[player.gun_holding].max_projectile_time;
                            projectile[pr].damage=guns[player.gun_holding].damage;
                            projectile[pr].speed=guns[player.gun_holding].proj_speed;
                            projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread+i*guns[player.gun_holding].pellet_spread;
                            projectile[pr].x=player.position.pos.x;
                            projectile[pr].y=player.position.pos.y;
                            projectile[pr].radius=guns[player.gun_holding].radius;
                            projectile[pr].distance_left=guns[player.gun_holding].max_distance;
                            projectile[pr].acceleration=guns[player.gun_holding].proj_acceleration;
                            projectile[pr].blast=guns[player.gun_holding].blast;
                            projectile[pr].blast.setPos(0.1);
                            projectile[pr].knockback=guns[player.gun_holding].knockback;
                            projectile[pr].gun=player.gun_holding;

                        }
                        pr=-1;
                        for (int j=0; j<projectile_count; j++)
                        {
                            if (projectile[j].damage<=0&&projectile[j].time<=0)
                            {
                                pr=j;
                                break;
                            }
                        }
                        if (pr>=0)
                        {//launches a projectile
                            projectile[pr].multiplier=guns[player.gun_holding].splash_multiplier;
                            projectile[pr].animation=guns[player.gun_holding].projectile;
                            projectile[pr].time=guns[player.gun_holding].max_projectile_time;
                            projectile[pr].damage=guns[player.gun_holding].damage;
                            projectile[pr].speed=guns[player.gun_holding].proj_speed;
                            projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread-i*guns[player.gun_holding].pellet_spread;
                            projectile[pr].x=player.position.pos.x;
                            projectile[pr].y=player.position.pos.y;
                            projectile[pr].radius=guns[player.gun_holding].radius;
                            projectile[pr].distance_left=guns[player.gun_holding].max_distance;
                            projectile[pr].acceleration=guns[player.gun_holding].proj_acceleration;
                            projectile[pr].blast=guns[player.gun_holding].blast;
                            projectile[pr].blast.setPos(0.1);
                            projectile[pr].knockback=guns[player.gun_holding].knockback;
                            projectile[pr].gun=player.gun_holding;

                        }
                        }
                    }
                    else
                    {
                       int dist=9999;
                    Bullet bullet;
                    Bullet subbullet;
                    int ty=0;
                    int nb=0;
                    for (int i=0; i<types; i++)
                    {
                        for (int j=0; j<enemy[i][0].quantity; j++)
                        {




                    if (enemy[i][j].health>0)
                    {
                        subbullet=shoot(enemy[i][j].position.pos.x, enemy[i][j].position.pos.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, spread+rotation(pos.x-960, pos.y-540), player.position.pos.x, player.position.pos.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance, mp);
                        if (subbullet.hit&&subbullet.distance<dist)
                        {
                            bullet=subbullet;
                            ty=i;
                            nb=j;
                            dist=subbullet.distance;
                        }
                    }
                    }
                    }

            if (dist==9999)
            {
                subbullet=shoot(0, 0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540), player.position.pos.x, player.position.pos.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance, mp);
            }
            if (bullet.hit)
            {
                enemy[ty][nb].health-=bullet.damage;
                enemy[ty][nb].position.speed.x+=cos(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y))*guns[player.gun_holding].knockback;
                enemy[ty][nb].position.speed.y+=sin(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y))*guns[player.gun_holding].knockback;
                guns[player.gun_holding].bullet.setScale(bullet.distance, sign1(pos.x-960));
                guns[player.gun_holding].bullet.setRotation(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y)*57);
            }
            else
            {
               guns[player.gun_holding].bullet.setScale(subbullet.distance, sign1(pos.x-960));
               guns[player.gun_holding].bullet.setRotation(rotation(subbullet.final_x-player.position.pos.x, subbullet.final_y-player.position.pos.y)*57);
            }
            guns[player.gun_holding].bullet.setPosition(960, 540);
            /*for (int i=0; i<10; i++)
                {
                    if (bullets[i].length<0.5)
                    {
                        //bullets[i].gun=player.gun_holding;
                        bullets[i].length=bullet.distance;
                        bullets[i].rotation=rotation(bullet.final_x-player.position.x, bullet.final_y-player.position.y)*57;
                        break;
                    }
                }*/

//multiplayer_map
            window.draw(guns[player.gun_holding].bullet);

            for (int k=1; k<=guns[player.gun_holding].pellets; k++)
            {
                dist=9999;
                for (int i=0; i<types; i++)
                    {
                        for (int j=0; j<enemy[i][0].quantity; j++)
                        {

                    if (enemy[i][j].health>0)
                    {//enemy[
                        subbullet=shoot(enemy[i][j].position.pos.x, enemy[i][j].position.pos.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, spread+rotation(pos.x-960, pos.y-540)+k*guns[player.gun_holding].pellet_spread, player.position.pos.x, player.position.pos.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance, mp);
                        if (subbullet.hit&&subbullet.distance<dist)
                        {
                            bullet=subbullet;
                            ty=i;
                            nb=j;
                            dist=subbullet.distance;
                        }
                    }
                        }
                    }

            //player.tiltmp[
            if (dist==9999)
            {
                subbullet=shoot(0, 0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540)+k*guns[player.gun_holding].pellet_spread, player.position.pos.x, player.position.pos.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance, mp);
            }
            if (bullet.hit)
            {
                enemy[ty][nb].health-=bullet.damage;
                enemy[ty][nb].position.speed.x+=cos(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y+k*guns[player.gun_holding].pellet_spread))*guns[player.gun_holding].knockback;
                enemy[ty][nb].position.speed.y+=sin(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y+k*guns[player.gun_holding].pellet_spread))*guns[player.gun_holding].knockback;
                guns[player.gun_holding].bullet.setScale(bullet.distance, sign1(pos.x-960));
                guns[player.gun_holding].bullet.setRotation(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y)*57/*+k*guns[player.gun_holding].pellet_spread*57*/);
            }
            else
            {
               guns[player.gun_holding].bullet.setScale(subbullet.distance, sign1(pos.x-960));
               guns[player.gun_holding].bullet.setRotation(rotation(subbullet.final_x-player.position.pos.x, subbullet.final_y-player.position.pos.y)*57/*+k*guns[player.gun_holding].pellet_spread*57*/);
            }
            guns[player.gun_holding].bullet.setPosition(960, 540);
            /*for (int i=0; i<10; i++)
                {
                    if (bullets[i].length<0.5)
                    {
                        //bullets[i].gun=player.gun_holding;
                        bullets[i].length=bullet.distance;
                        bullets[i].rotation=rotation(bullet.final_x-player.position.x, bullet.final_y-player.position.y)*57;
                        break;
                    }
                }*/


            window.draw(guns[player.gun_holding].bullet);
            dist=9999;
            for (int i=0; i<types; i++)
                    {
                        for (int j=0; j<enemy[i][0].quantity; j++)
                        {

                    if (enemy[i][j].health>0)
                    {
                        subbullet=shoot(enemy[i][j].position.pos.x, enemy[i][j].position.pos.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, spread+rotation(pos.x-960, pos.y-540)-k*guns[player.gun_holding].pellet_spread, player.position.pos.x, player.position.pos.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance, mp);
                        if (subbullet.hit&&subbullet.distance<dist)
                        {
                            bullet=subbullet;
                            ty=i;
                            nb=j;
                            dist=subbullet.distance;
                        }
                    }
                        }
                    }


            if (dist==9999)
            {
                //subbullet=smp[hoot(0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540), player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                //subbullet=shoot(0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540)+k*guns[player.gun_holding].pellet_spread, player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                subbullet=shoot(0, 0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540)-k*guns[player.gun_holding].pellet_spread, player.position.pos.x, player.position.pos.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance, mp);

            }
            if (bullet.hit)
            {
                enemy[ty][nb].health-=bullet.damage;
                enemy[ty][nb].position.speed.x+=cos(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y-k*guns[player.gun_holding].pellet_spread))*guns[player.gun_holding].knockback;
                enemy[ty][nb].position.speed.y+=sin(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y-k*guns[player.gun_holding].pellet_spread))*guns[player.gun_holding].knockback;
                guns[player.gun_holding].bullet.setScale(bullet.distance, sign1(pos.x-960));
               guns[player.gun_holding].bullet.setRotation(rotation(bullet.final_x-player.position.pos.x, bullet.final_y-player.position.pos.y)*57/*-k*guns[player.gun_holding].pellet_spread*57*/);

            }
            else
            {
               guns[player.gun_holding].bullet.setScale(subbullet.distance, sign1(pos.x-960));
               guns[player.gun_holding].bullet.setRotation(rotation(subbullet.final_x-player.position.pos.x, subbullet.final_y-player.position.pos.y)*57/*-k*guns[player.gun_holding].pellet_spread*57*/);
            }
            guns[player.gun_holding].bullet.setPosition(960, 540);
            /*for (int i=0; i<10; i++)
                {
                    if (bullets[i].length<0.5)
                    {
                        //bullets[i].gun=player.gun_holding;
                        bullets[i].length=bullet.distance;
                        bullets[i].rotation=rotation(bullet.final_x-player.position.x, bullet.final_y-player.position.y)*57;
                        break;
                    }
                }*/


            window.draw(guns[player.gun_holding].bullet);
            }

                    }
                    //

                    player.position.speed.x-=cos(rotation(pos.x-960, pos.y-540))*guns[player.gun_holding].self_knockback;
                    player.position.speed.y-=sin(rotation(pos.x-960, pos.y-540))*guns[player.gun_holding].self_knockback;
                }

                //
                guns[player.gun_holding].pre.setFrame(guns[player.gun_holding].predelay);
                guns[player.gun_holding].left_pre.setFrame(guns[player.gun_holding].predelay);
                guns[player.gun_holding].right_pre.setFrame(guns[player.gun_holding].predelay);

                //
                if (pos.x>=960)
                {

                    guns[player.gun_holding].pre.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left_pre.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));

                    guns[player.gun_holding].right_pre.setPR(1, 960, 540, player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));

                    player.body.setPR(1, 960, 540, 0);
                    player.body.step(player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                else
                {

                    guns[player.gun_holding].pre.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left_pre.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].right_pre.setPR(-1, 960, 540, -player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));
                    player.body.setPR(-1, 960, 540, 0);
                    player.body.step(-player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(-1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
                window.draw(guns[player.gun_holding].left_pre.sprite);
                window.draw(guns[player.gun_holding].pre.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(guns[player.gun_holding].right_pre.sprite);
            }
            else if (guns[player.gun_holding].reload_counter>0)
            {
                //std::cout << "Test1";
                guns[player.gun_holding].reload_counter--;
                if (guns[player.gun_holding].reload_counter<1)
                {
                    if (guns[player.gun_holding].ammo+guns[player.gun_holding].max_load>=guns[player.gun_holding].max_ammo)
                    {
                        guns[player.gun_holding].ammo=guns[player.gun_holding].max_ammo;
                    }
                    else
                    {
                        guns[player.gun_holding].ammo+=guns[player.gun_holding].max_load;
                        if (!cancel)
                        {
                            guns[player.gun_holding].reload_sound.play();
                            guns[player.gun_holding].reload_counter=guns[player.gun_holding].max_reload;
                            player.reload_play=true;
                        }
                    }
                }
                //std::cout << guns[player.gun_holding].reload_counter;
                guns[player.gun_holding].reload.setFrame(guns[player.gun_holding].reload_counter);
                guns[player.gun_holding].left_reload.setFrame(guns[player.gun_holding].reload_counter);
                guns[player.gun_holding].right_reload.setFrame(guns[player.gun_holding].reload_counter);
                //std::cout << "Test2";
                if (pos.x>=960)
                {

                    guns[player.gun_holding].reload.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left_reload.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));

                    guns[player.gun_holding].right_reload.setPR(1, 960, 540, player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));

                    player.body.setPR(1, 960, 540, 0);
                    player.body.step(player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                else
                {

                    guns[player.gun_holding].reload.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left_reload.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].right_reload.setPR(-1, 960, 540, -player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));
                    player.body.setPR(-1, 960, 540, 0);
                    player.body.step(-player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(-1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }

                window.draw(guns[player.gun_holding].left_reload.sprite);
                window.draw(guns[player.gun_holding].reload.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(guns[player.gun_holding].right_reload.sprite);
            }
            else if (guns[player.gun_holding].deploy_counter>0)
            {
                guns[player.gun_holding].animation.setFrame(0);
                guns[player.gun_holding].left.setFrame(0);
                guns[player.gun_holding].right.setFrame(0);

                if (pos.x>=960)
                {

                    guns[player.gun_holding].animation.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));

                    guns[player.gun_holding].right.setPR(1, 960, 540, player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));

                    player.body.setPR(1, 960, 540, 0);
                    player.body.step(player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                else
                {

                    guns[player.gun_holding].animation.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].right.setPR(-1, 960, 540, -player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));
                    player.body.setPR(-1, 960, 540, 0);
                    player.body.step(-player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(-1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }

                window.draw(guns[player.gun_holding].left.sprite);
                window.draw(guns[player.gun_holding].animation.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(guns[player.gun_holding].right.sprite);
            }
            else
            {
                guns[player.gun_holding].animation.setFrame(guns[player.gun_holding].delay);
                guns[player.gun_holding].left.setFrame(guns[player.gun_holding].delay);
                guns[player.gun_holding].right.setFrame(guns[player.gun_holding].delay);



                if (pos.x>=960)
                {

                    guns[player.gun_holding].animation.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left.setPR(1, 960, 540, player.tilt+rt(pos.x-960, pos.y-540));

                    guns[player.gun_holding].right.setPR(1, 960, 540, player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));

                    player.body.setPR(1, 960, 540, 0);
                    player.body.step(player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                else
                {

                    guns[player.gun_holding].animation.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].left.setPR(-1, 960, 540, -player.tilt+rt(pos.x-960, pos.y-540));
                    guns[player.gun_holding].right.setPR(-1, 960, 540, -player.tilt+!(guns[player.gun_holding].isPistol&&guns[player.gun_holding].reload_counter<1)*rt(pos.x-960, pos.y-540));
                    player.body.setPR(-1, 960, 540, 0);
                    player.body.step(-player.position.speed.x*(0.16/player.max_speed));
                    player.head.setPR(-1, 960, 540, rt(pos.x-960, pos.y-540));
                }
                if (player.position.speed.x<0.1&&player.position.speed.x>-0.1)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.idle);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }
            if (!player.isStanding)
            {
                player.body.pos=0;


                player.body.sprite.setTexture(player.jump);
                player.body.sprite.setTextureRect(IntRect(0, 0, 100, 100));
            }

                window.draw(guns[player.gun_holding].left.sprite);
                window.draw(guns[player.gun_holding].animation.sprite);

                window.draw(player.body.sprite);
                window.draw(player.head.sprite);

                window.draw(guns[player.gun_holding].right.sprite);
            }
            if (guns[player.gun_holding].reload_counter<1)
            {
                cancel=false;
            }
            if (Mouse::isButtonPressed(Mouse::Left))
            {
                cancel=true;
            }


        /*guns[player.gun_holding].sprite1.setTextureRect(IntRect(guns[player.gun_holding].positionx[guns[player.gun_holding].delay], 0, guns[player.gun_holding].width, guns[player.gun_holding].height));
        guns[player.gun_holding].sprite2.setTextureRect(IntRect(guns[player.gun_holding].positionx[guns[player.gun_holding].delay], 0, guns[player.gun_holding].width, guns[player.gun_holding].height));
        guns[player.gun_holding].sprite3.setTextureRect(IntRect(guns[player.gun_holding].positionx[guns[player.gun_holding].delay], 0, guns[player.gun_holding].width, guns[player.gun_holding].height));
        guns[player.gun_holding].sprite4.setTextureRect(IntRect(guns[player.gun_holding].positionx[guns[player.gun_holding].delay], 0, guns[player.gun_holding].width, guns[player.gun_holding].height));

        guns[player.gun_holding].sprite1.setRotation(rt(pos.x-960, pos.y-540)+player.tilt+player.deploy*sign1(pos.x-960));
        guns[player.gun_holding].sprite2.setRotation(rt(pos.x-960, pos.y-540)+270+player.tilt+player.deploy*sign1(pos.x-960));
        guns[player.gun_holding].sprite3.setRotation(rt(pos.x-960, pos.y-540)+180+player.tilt+player.deploy*sign1(pos.x-960));
        guns[player.gun_holding].sprite4.setRotation(rt(pos.x-960, pos.y-540)+90+player.tilt+player.deploy*sign1(pos.x-960));

        guns[player.gun_holding].sprite1.setPosition(960, 540);
        guns[player.gun_holding].sprite2.setPosition(960, 540);
        guns[player.gun_holding].sprite3.setPosition(960, 540);
        guns[player.gun_holding].sprite4.setPosition(960, 540);

        player.head2.setRotation(rt(pos.x-960, pos.y-540)+270);
        player.head3.setRotation(rt(pos.x-960, pos.y-540)+180);



        player.hands[player.gun_holding].right1.setTextureRect(IntRect(guns[player.gun_holding].right_positionx[guns[player.gun_holding].delay], 0, 49, 49));
        player.hands[player.gun_holding].right2.setTextureRect(IntRect(guns[player.gun_holding].right_positionx[guns[player.gun_holding].delay], 0, 49, 49));
        player.hands[player.gun_holding].right3.setTextureRect(IntRect(guns[player.gun_holding].right_positionx[guns[player.gun_holding].delay], 0, 49, 49));
        player.hands[player.gun_holding].right4.setTextureRect(IntRect(guns[player.gun_holding].right_positionx[guns[player.gun_holding].delay], 0, 49, 49));

        if (guns[player.gun_holding].isPistol)
        {
            player.hands[player.gun_holding].right1.setRotation(player.tilt);
            player.hands[player.gun_holding].right2.setRotation(270+player.tilt);
            player.hands[player.gun_holding].right3.setRotation(180+player.tilt);
            player.hands[player.gun_holding].right4.setRotation(90+player.tilt);
        }
        else
        {
            player.hands[player.gun_holding].right1.setRotation(rt(pos.x-960, pos.y-540)+player.tilt+player.deploy*sign1(pos.x-960));
            player.hands[player.gun_holding].right2.setRotation(rt(pos.x-960, pos.y-540)+270+player.tilt+player.deploy*sign1(pos.x-960));
            player.hands[player.gun_holding].right3.setRotation(rt(pos.x-960, pos.y-540)+180+player.tilt+player.deploy*sign1(pos.x-960));
            player.hands[player.gun_holding].right4.setRotation(rt(pos.x-960, pos.y-540)+90+player.tilt+player.deploy*sign1(pos.x-960));
        }




        player.hands[player.gun_holding].left1.setTextureRect(IntRect(guns[player.gun_holding].left_positionx[guns[player.gun_holding].delay], 0, 49, 49));
        player.hands[player.gun_holding].left2.setTextureRect(IntRect(guns[player.gun_holding].left_positionx[guns[player.gun_holding].delay], 0, 49, 49));
        player.hands[player.gun_holding].left3.setTextureRect(IntRect(guns[player.gun_holding].left_positionx[guns[player.gun_holding].delay], 0, 49, 49));
        player.hands[player.gun_holding].left4.setTextureRect(IntRect(guns[player.gun_holding].left_positionx[guns[player.gun_holding].delay], 0, 49, 49));

        player.hands[player.gun_holding].left1.setRotation(rt(pos.x-960, pos.y-540)+player.tilt+player.deploy*sign1(pos.x-960));
        player.hands[player.gun_holding].left2.setRotation(rt(pos.x-960, pos.y-540)+270+player.tilt+player.deploy*sign1(pos.x-960));
        player.hands[player.gun_holding].left3.setRotation(rt(pos.x-960, pos.y-540)+180+player.tilt+player.deploy*sign1(pos.x-960));
        player.hands[player.gun_holding].left4.setRotation(rt(pos.x-960, pos.y-540)+90+player.tilt+player.deploy*sign1(pos.x-960));*/

        /*if (Mouse::isButtonPressed(Mouse::Left)&&guns[player.gun_holding].delay==0&&!player.deploy)
        {
            double spread=random(guns[player.gun_holding].spread);
            guns[player.gun_holding].sound.play();
            guns[player.gun_holding].delay=guns[player.gun_holding].max_delay;
            if (!guns[player.gun_holding].isProjectile)
            {
             dist=9999;

            for(int i=0; i<types; i++)
            {
                for (int j=0; j<enemy_count; j++)

                {
                    if (enemy[i][j].health>0)
                    {
                        subbullet=shoot(enemy[i][j].position.x, enemy[i][j].position.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, spread+rotation(pos.x-960, pos.y-540), player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                        if (subbullet.hit&&subbullet.distance<dist)
                        {
                            bullet=subbullet;
                            ty=i;
                            nb=j;
                            dist=subbullet.distance;
                        }
                    }

                }
            }
            if (isVictory==true)
            {
                subbullet=shoot(0, 0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540), player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
            }
            if (bullet.hit)
            {
                enemy[ty][nb].health-=bullet.damage;
                guns[player.gun_holding].bullet.setScale(bullet.distance, sign1(pos.x-960));
                guns[player.gun_holding].bullet.setRotation(rotation(bullet.final_x-player.position.x, bullet.final_y-player.position.y)*57);
            }
            else
            {
               guns[player.gun_holding].bullet.setScale(subbullet.distance, sign1(pos.x-960));
               guns[player.gun_holding].bullet.setRotation(rotation(subbullet.final_x-player.position.x, subbullet.final_y-player.position.y)*57);
            }
            guns[player.gun_holding].bullet.setPosition(960, 540);


            window.draw(guns[player.gun_holding].bullet);

            for (int k=1; k<=guns[player.gun_holding].pellets; k++)
            {
                dist=9999;
                for(int i=0; i<types; i++)
            {
                for (int j=0; j<enemy_count; j++)

                {
                    if (enemy[i][j].health>0)
                    {
                        subbullet=shoot(enemy[i][j].position.x, enemy[i][j].position.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, spread+rotation(pos.x-960, pos.y-540)+k*guns[player.gun_holding].pellet_spread, player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                        if (subbullet.hit&&subbullet.distance<dist)
                        {
                            bullet=subbullet;
                            ty=i;
                            nb=j;
                            dist=subbullet.distance;
                        }
                    }

                }
            }//player.tilt
            if (isVictory==true)
            {
                subbullet=shoot(0, 0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540)+k*guns[player.gun_holding].pellet_spread, player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
            }
            if (bullet.hit)
            {
                enemy[ty][nb].health-=bullet.damage;
                guns[player.gun_holding].bullet.setScale(bullet.distance, sign1(pos.x-960));
                guns[player.gun_holding].bullet.setRotation(rotation(bullet.final_x-player.position.x, bullet.final_y-player.position.y)*57+k*guns[player.gun_holding].pellet_spread*57);
            }
            else
            {
               guns[player.gun_holding].bullet.setScale(subbullet.distance, sign1(pos.x-960));
               guns[player.gun_holding].bullet.setRotation(rotation(subbullet.final_x-player.position.x, subbullet.final_y-player.position.y)*57+k*guns[player.gun_holding].pellet_spread*57);
            }
            guns[player.gun_holding].bullet.setPosition(960, 540);


            window.draw(guns[player.gun_holding].bullet);
            dist=9999;
            for(int i=0; i<types; i++)
            {
                for (int j=0; j<enemy_count; j++)

                {
                    if (enemy[i][j].health>0)
                    {
                        subbullet=shoot(enemy[i][j].position.x, enemy[i][j].position.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, spread+rotation(pos.x-960, pos.y-540)-k*guns[player.gun_holding].pellet_spread, player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                        if (subbullet.hit&&subbullet.distance<dist)
                        {
                            bullet=subbullet;
                            ty=i;
                            nb=j;
                            dist=subbullet.distance;
                        }
                    }

                }
            }
            if (isVictory==true)
            {
                //subbullet=shoot(0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540), player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                //subbullet=shoot(0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540)+k*guns[player.gun_holding].pellet_spread, player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);
                subbullet=shoot(0, 0, 0, 0, 0, spread+rotation(pos.x-960, pos.y-540)-k*guns[player.gun_holding].pellet_spread, player.position.x, player.position.y, guns[player.gun_holding].damage, guns[player.gun_holding].max_distance);

            }
            if (bullet.hit)
            {
                enemy[ty][nb].health-=bullet.damage;
                guns[player.gun_holding].bullet.setScale(bullet.distance, sign1(pos.x-960));
                guns[player.gun_holding].bullet.setRotation(rotation(bullet.final_x-player.position.x, bullet.final_y-player.position.y)*57-k*guns[player.gun_holding].pellet_spread*57);
            }
            else
            {
               guns[player.gun_holding].bullet.setScale(subbullet.distance, sign1(pos.x-960));
               guns[player.gun_holding].bullet.setRotation(rotation(subbullet.final_x-player.position.x, subbullet.final_y-player.position.y)*57-k*guns[player.gun_holding].pellet_spread*57);
            }
            guns[player.gun_holding].bullet.setPosition(960, 540);


            window.draw(guns[player.gun_holding].bullet);
            }
            }
            else
            {
                int pr=-1;
                for (int i=0; i<projectile_count; i++)
                {
                    if (projectile[i].damage<=0&&projectile[i].time<=0)
                    {
                        pr=i;
                        break;
                    }
                }
                if (pr>=0)
                {
                    projectile[pr].multiplier=guns[player.gun_holding].splash_multiplier;
                    projectile[pr].gun=player.gun_holding;
                    projectile[pr].time=guns[player.gun_holding].max_projectile_time;
                    projectile[pr].damage=guns[player.gun_holding].damage;
                    projectile[pr].speed=guns[player.gun_holding].proj_speed;
                    projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread;
                    projectile[pr].x=player.position.x;
                    projectile[pr].y=player.position.y;
                    projectile[pr].radius=guns[player.gun_holding].radius;
                    projectile[pr].distance_left=guns[player.gun_holding].max_distance;
                    projectile[pr].acceleration=guns[player.gun_holding].proj_acceleration;
                    projectile[pr].explosion.setBuffer(guns[player.gun_holding].exp_buffer);
                    projectile[pr].sprite1.setTexture(guns[player.gun_holding].proj_texture1);
                    projectile[pr].sprite2.setTexture(guns[player.gun_holding].proj_texture2);
                    projectile[pr].sprite3.setTexture(guns[player.gun_holding].proj_texture3);
                    projectile[pr].sprite4.setTexture(guns[player.gun_holding].proj_texture4);
                    projectile[pr].sprite1.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_length, guns[player.gun_holding].proj_width));
                    projectile[pr].sprite2.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_width, guns[player.gun_holding].proj_length));
                    projectile[pr].sprite3.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_length, guns[player.gun_holding].proj_width));
                    projectile[pr].sprite4.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_width, guns[player.gun_holding].proj_length));
                    projectile[pr].sprite1.setRotation(projectile[pr].rotation*57);
                    projectile[pr].sprite2.setRotation(270+projectile[pr].rotation*57);
                    projectile[pr].sprite3.setRotation(180+projectile[pr].rotation*57);
                    projectile[pr].sprite4.setRotation(90+projectile[pr].rotation*57);
                    projectile[pr].blast.setTexture(guns[player.gun_holding].blast);
                    projectile[pr].blast.setTextureRect(IntRect(0, 0, 2*guns[player.gun_holding].radius, 2*guns[player.gun_holding].radius));
                }
                for (int i=1; i<=guns[player.gun_holding].pellets; i++)
                {
                    pr=-1;
                for (int i=0; i<projectile_count; i++)
                {
                    if (projectile[i].damage<=0&&projectile[i].time<=0)
                    {
                        pr=i;
                        break;
                    }
                }
                if (pr>=0)
                {
                    projectile[pr].multiplier=guns[player.gun_holding].splash_multiplier;
                    projectile[pr].gun=player.gun_holding;
                    projectile[pr].time=guns[player.gun_holding].max_projectile_time;
                    projectile[pr].damage=guns[player.gun_holding].damage;
                    projectile[pr].speed=guns[player.gun_holding].proj_speed;
                    projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread+i*guns[player.gun_holding].pellet_spread;
                    projectile[pr].x=player.position.x;
                    projectile[pr].y=player.position.y;
                    projectile[pr].radius=guns[player.gun_holding].radius;
                    projectile[pr].distance_left=guns[player.gun_holding].max_distance;
                    projectile[pr].acceleration=guns[player.gun_holding].proj_acceleration;
                    projectile[pr].explosion.setBuffer(guns[player.gun_holding].exp_buffer);
                    projectile[pr].sprite1.setTexture(guns[player.gun_holding].proj_texture1);
                    projectile[pr].sprite2.setTexture(guns[player.gun_holding].proj_texture2);
                    projectile[pr].sprite3.setTexture(guns[player.gun_holding].proj_texture3);
                    projectile[pr].sprite4.setTexture(guns[player.gun_holding].proj_texture4);
                    projectile[pr].sprite1.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_length, guns[player.gun_holding].proj_width));
                    projectile[pr].sprite2.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_width, guns[player.gun_holding].proj_length));
                    projectile[pr].sprite3.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_length, guns[player.gun_holding].proj_width));
                    projectile[pr].sprite4.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_width, guns[player.gun_holding].proj_length));
                    projectile[pr].sprite1.setRotation(projectile[pr].rotation*57);
                    projectile[pr].sprite2.setRotation(270+projectile[pr].rotation*57);
                    projectile[pr].sprite3.setRotation(180+projectile[pr].rotation*57);
                    projectile[pr].sprite4.setRotation(90+projectile[pr].rotation*57);
                    projectile[pr].blast.setTexture(guns[player.gun_holding].blast);
                    projectile[pr].blast.setTextureRect(IntRect(0, 0, 2*guns[player.gun_holding].radius, 2*guns[player.gun_holding].radius));
                }

                pr=-1;
                for (int i=0; i<projectile_count; i++)
                {
                    if (projectile[i].damage<=0&&projectile[i].time<=0)
                    {
                        pr=i;
                        break;
                    }
                }
                if (pr>=0)
                {
                    projectile[pr].multiplier=guns[player.gun_holding].splash_multiplier;
                    projectile[pr].gun=player.gun_holding;
                    projectile[pr].time=guns[player.gun_holding].max_projectile_time;
                    projectile[pr].damage=guns[player.gun_holding].damage;
                    projectile[pr].speed=guns[player.gun_holding].proj_speed;
                    projectile[pr].rotation=rotation(pos.x-960, pos.y-540)+spread-i*guns[player.gun_holding].pellet_spread;
                    projectile[pr].x=player.position.x;
                    projectile[pr].y=player.position.y;
                    projectile[pr].radius=guns[player.gun_holding].radius;
                    projectile[pr].distance_left=guns[player.gun_holding].max_distance;
                    projectile[pr].acceleration=guns[player.gun_holding].proj_acceleration;
                    projectile[pr].explosion.setBuffer(guns[player.gun_holding].exp_buffer);
                    projectile[pr].sprite1.setTexture(guns[player.gun_holding].proj_texture1);
                    projectile[pr].sprite2.setTexture(guns[player.gun_holding].proj_texture2);
                    projectile[pr].sprite3.setTexture(guns[player.gun_holding].proj_texture3);
                    projectile[pr].sprite4.setTexture(guns[player.gun_holding].proj_texture4);
                    projectile[pr].sprite1.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_length, guns[player.gun_holding].proj_width));
                    projectile[pr].sprite2.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_width, guns[player.gun_holding].proj_length));
                    projectile[pr].sprite3.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_length, guns[player.gun_holding].proj_width));
                    projectile[pr].sprite4.setTextureRect(IntRect(0, 0, guns[player.gun_holding].proj_width, guns[player.gun_holding].proj_length));
                    projectile[pr].sprite1.setRotation(projectile[pr].rotation*57);
                    projectile[pr].sprite2.setRotation(270+projectile[pr].rotation*57);
                    projectile[pr].sprite3.setRotation(180+projectile[pr].rotation*57);
                    projectile[pr].sprite4.setRotation(90+projectile[pr].rotation*57);
                    projectile[pr].blast.setTexture(guns[player.gun_holding].blast);
                    projectile[pr].blast.setTextureRect(IntRect(0, 0, 2*guns[player.gun_holding].radius, 2*guns[player.gun_holding].radius));
                }
                }
            }



        }*/

        /*for (int k=0; k<projectile_count; k++)
        {
            if (projectile[k].damage<=0)
            {
                if (projectile[k].time)
                {
                    projectile[k].time--;
                    projectile[k].blast.setPosition(960+projectile[k].x-player.position.x-projectile[k].radius,540+projectile[k].y-player.position.y-projectile[k].radius);
                    window.draw(projectile[k].blast);
                }
            }
            if (projectile[k].damage>0)
            {
            dist=9999;
            bullet.distance=0;
            for(int i=0; i<types; i++)
            {
                for (int j=0; j<enemy_count; j++)
                {
                    if (enemy[i][j].health>0)
                    {
                        subbullet=shoot(enemy[i][j].position.x, enemy[i][j].position.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, projectile[k].rotation, projectile[k].x, projectile[k].y, projectile[k].damage, projectile[k].speed);
                        if (subbullet.distance<dist)
                        {
                            bullet=subbullet;
                            dist=subbullet.distance;
                        }
                    }
                }
            }
            if (isVictory)
            {
                bullet=shoot(0, 0, 0, 0, 0, projectile[k].rotation, projectile[k].x, projectile[k].y, projectile[k].damage, projectile[k].speed);
                dist=bullet.distance;
            }
            if (dist<projectile[k].speed||projectile[k].distance_left<=0)
            {
                projectile[k].x+=(bullet.distance-1)*cos(projectile[k].rotation);
                projectile[k].y+=(bullet.distance-1)*sin(projectile[k].rotation);
                for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy_count; j++)
                    {
                        if (enemy[i][j].health>0)
                        {
                            enemy[i][j].health-=damage(projectile[k].multiplier, enemy[i][j].position.x, enemy[i][j].position.y, enemy[i][j].width, enemy[i][j].position.y-enemy[i][j].head_height, enemy[i][j].position.y+enemy[i][j].height, projectile[k].x, projectile[k].y, projectile[k].radius, projectile[k].damage);
                        }

                    }
                }
                projectile[k].damage=0;
                projectile[k].explosion.play();
                projectile[k].blast.setPosition(960+projectile[k].x-player.position.x-projectile[k].radius,540+projectile[k].y-player.position.y-projectile[k].radius);
                window.draw(projectile[k].blast);
            }
            else
            {
                projectile[k].x+=cos(projectile[k].rotation)*(projectile[k].speed-1);
                projectile[k].y+=sin(projectile[k].rotation)*(projectile[k].speed-1);
                projectile[k].distance_left-=(projectile[k].speed-1);
            }
            projectile[k].sprite1.setPosition(960+projectile[k].x-player.position.x,540+projectile[k].y-player.position.y);
            projectile[k].sprite2.setPosition(960+projectile[k].x-player.position.x,540+projectile[k].y-player.position.y);
            projectile[k].sprite3.setPosition(960+projectile[k].x-player.position.x,540+projectile[k].y-player.position.y);
            projectile[k].sprite4.setPosition(960+projectile[k].x-player.position.x,540+projectile[k].y-player.position.y);
            window.draw(projectile[k].sprite1);
            window.draw(projectile[k].sprite2);
            window.draw(projectile[k].sprite3);
            window.draw(projectile[k].sprite4);
            projectile[k].speed+=projectile[k].acceleration;
            }

        }*/
        for (int k=0; k<projectile_count; k++)
            {
                if (projectile[k].damage<=0&&projectile[k].time)
                {
                    projectile[k].time--;
                    projectile[k].blast.setPR(1, round1(960-player.position.pos.x+projectile[k].x), round1(540-player.position.pos.y+projectile[k].y), 0);

                    projectile[k].blast.setFrame(projectile[k].time);
                    window.draw(projectile[k].blast.sprite);
                }
                if (projectile[k].damage>0)
                {
                    int dist=9999;
                Bullet bullet;
                Bullet subbullet;
                bullet.distance=0;
                bool b=true;

                for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {


//multiplayer_map
                        if (enemy[i][j].health>0)
                        {
                            b=false;
                            subbullet=shoot(enemy[i][j].position.pos.x, enemy[i][j].position.pos.y, enemy[i][j].head_height, enemy[i][j].height, enemy[i][j].width, projectile[k].rotation, projectile[k].x, projectile[k].y, projectile[k].damage, projectile[k].speed, mp);
                            if (subbullet.distance<dist)
                            {
                                bullet=subbullet;
                                dist=subbullet.distance;
                            }
                        }
                        }
                }
                if (b)
                    bullet=shoot(0, 0, 0, 0, 0, projectile[k].rotation, projectile[k].x, projectile[k].y, projectile[k].damage, projectile[k].speed, mp);
                dist=bullet.distance;

                    //mp[
                    if (dist<projectile[k].speed||projectile[k].distance_left<=0)
                    {

                        projectile[k].x+=(bullet.distance-1)*cos(projectile[k].rotation);
                        projectile[k].y+=(bullet.distance-1)*sin(projectile[k].rotation);
                        Bullet dmg=damage(projectile[k].multiplier, player.position.pos.x, player.position.pos.y, player.width, player.position.pos.y-player.head_height, player.position.pos.y+player.height, projectile[k].x, projectile[k].y, projectile[k].radius, projectile[k].damage, mp.M);

                        player.position.speed.x+=cos(rotation(dmg.final_x, dmg.final_y))*guns[projectile[k].gun].explosion_knockback*double(dmg.damage)/projectile[k].damage;
                        player.position.speed.y+=sin(rotation(dmg.final_x, dmg.final_y))*guns[projectile[k].gun].explosion_knockback*double(dmg.damage)/projectile[k].damage;
                        player.health-=round1(double(dmg.damage)*guns[projectile[k].gun].self_damage_multiplier);


                        for (int i=0; i<types; i++)
                {
                    for (int j=0; j<enemy[i][0].quantity; j++)
                    {

                                if (enemy[i][j].health>0)
                                {
                                    dmg=damage(projectile[k].multiplier, enemy[i][j].position.pos.x, enemy[i][j].position.pos.y, enemy[i][j].width, enemy[i][j].position.pos.y-enemy[i][j].head_height, enemy[i][j].position.pos.y+enemy[i][j].height, projectile[k].x, projectile[k].y, projectile[k].radius, projectile[k].damage, mp.M);
                                    //dmgEnemy+=dmg;
                                    enemy[i][j].health-=round1(dmg.damage);
                                    enemy[i][j].position.speed.x+=cos(projectile[k].rotation)*projectile[k].knockback*double(dmg.damage)/projectile[k].damage;
                                    enemy[i][j].position.speed.y+=sin(projectile[k].rotation)*projectile[k].knockback*double(dmg.damage)/projectile[k].damage;
                                    enemy[i][j].position.speed.x+=cos(rotation(dmg.final_x, dmg.final_y))*guns[projectile[k].gun].explosion_knockback*double(dmg.damage)/projectile[k].damage;
                                    enemy[i][j].position.speed.y+=sin(rotation(dmg.final_x, dmg.final_y))*guns[projectile[k].gun].explosion_knockback*double(dmg.damage)/projectile[k].damage;

                                }
                    }
                }

                        projectile[k].damage=0;
                        projectile[k].explosion.setBuffer(guns[projectile[k].gun].exp_buffer);
                        projectile[k].explosion.play();
                        //projectile[k].explosion.play();
                        projectile[k].blast.setPos(0.1);
                        projectile[k].blast.setPR(1, projectile[k].x, projectile[k].y, 0);
                        //window.draw(projectile[k].blast);
                    }
                    else
                    {
                        projectile[k].x+=cos(projectile[k].rotation)*(projectile[k].speed-1);
                        projectile[k].y+=sin(projectile[k].rotation)*(projectile[k].speed-1);
                        projectile[k].distance_left-=(projectile[k].speed-1);
                    }
                    //Mouse

                projectile[k].animation.setPR(sign1(cos(projectile[k].rotation)), 960+projectile[k].x-player.position.pos.x, 540+projectile[k].y-player.position.pos.y, rt(cos(projectile[k].rotation), sin(projectile[k].rotation)));
                projectile[k].animation.setFrame(round1(projectile[k].distance_left/projectile[k].speed));
                window.draw(projectile[k].animation.sprite);
                projectile[k].speed+=projectile[k].acceleration;
                }
                //projectiles[k].gun=projectile[k].gun;
               // projectiles[k].x=projectile[k].x;
               // projectiles[k].y=projectile[k].y;
                //projectiles[k].damage=projectile[k].damage;
                //projectiles[k].rotation=projectile[k].rotation;
                //projectiles[k].distance_left=projectile[k].distance_left;
                //projectiles[k].time=projectile[k].time;
            }

        /*if (pos.x>=960)
        {
            if (Keyboard::isKeyPressed(Keyboard::D)&&!isStanding)
        {
            player.position.speed_x+=player.air_strafe_force;
        }
        if (Keyboard::isKeyPressed(Keyboard::A)&&!isStanding)
        {
            player.position.speed_x-=player.air_strafe_force;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)&&isStanding)
        {
            player.position.speed_x+=player.strafe_force;

            if (player.tilt>=10)
                {
                    player.tilt_speed=-1;
                }
                else if (player.tilt<=-10)
                {
                    player.tilt_speed=1;
                }
                player.tilt+=player.tilt_speed;
                if (player.body_frame_counter<29)
                    player.body_frame_counter++;
                else
                    player.body_frame_counter=0;

        }
        else if (Keyboard::isKeyPressed(Keyboard::A)&&isStanding)
        {
            player.position.speed_x-=player.strafe_force;


            if (player.tilt>=10)
                {
                    player.tilt_speed=-1;
                }
                else if (player.tilt<=-10)
                {
                    player.tilt_speed=1;
                }
                player.tilt+=player.tilt_speed;

                    if (player.body_frame_counter>0)
                    player.body_frame_counter--;
                else
                    player.body_frame_counter=29;
        }
        else
        {
            player.body_frame_counter=0;
            player.tilt=0;
            player.tilt_speed=1;
        }


            guns[player.gun_holding].sprite1.setScale(1, 1);
            guns[player.gun_holding].sprite2.setScale(1, 1);
            guns[player.gun_holding].sprite3.setScale(1, 1);
            guns[player.gun_holding].sprite4.setScale(1, 1);

            player.body1.setScale(1, 1);
            player.head2.setScale(1, 1);
            player.head3.setScale(1, 1);
            player.body4.setScale(1, 1);

            player.hands[player.gun_holding].left1.setScale(1, 1);
            player.hands[player.gun_holding].left2.setScale(1, 1);
            player.hands[player.gun_holding].left3.setScale(1, 1);
            player.hands[player.gun_holding].left4.setScale(1, 1);

            player.hands[player.gun_holding].right1.setScale(1, 1);
            player.hands[player.gun_holding].right2.setScale(1, 1);
            player.hands[player.gun_holding].right3.setScale(1, 1);
            player.hands[player.gun_holding].right4.setScale(1, 1);
        }
        else
        {
            if (Keyboard::isKeyPressed(Keyboard::D)&&!isStanding)
        {
            player.position.speed_x+=player.air_strafe_force;
        }
        if (Keyboard::isKeyPressed(Keyboard::A)&&!isStanding)
        {
            player.position.speed_x-=player.air_strafe_force;
        }
        if (Keyboard::isKeyPressed(Keyboard::D)&&isStanding)
        {
            player.position.speed_x+=player.strafe_force;

            if (player.tilt>=10)
                {
                    player.tilt_speed=-1;
                }
                else if (player.tilt<=-10)
                {
                    player.tilt_speed=1;
                }
                player.tilt+=player.tilt_speed;
                if (player.body_frame_counter>0)
                    player.body_frame_counter--;
                else
                    player.body_frame_counter=29;
        }
        else if (Keyboard::isKeyPressed(Keyboard::A)&&isStanding)
        {
            player.position.speed_x-=player.strafe_force;


            if (player.tilt>=10)
                {
                    player.tilt_speed=-1;
                }
                else if (player.tilt<=-10)
                {
                    player.tilt_speed=1;
                }
                player.tilt+=player.tilt_speed;
                if (player.body_frame_counter<29)
                    player.body_frame_counter++;
                else
                    player.body_frame_counter=0;
        }
        else
        {
            player.body_frame_counter=0;
            player.tilt=0;
            player.tilt_speed=-1;
        }

            guns[player.gun_holding].sprite1.setScale(-1, 1);
            guns[player.gun_holding].sprite2.setScale(1, -1);
            guns[player.gun_holding].sprite3.setScale(-1, 1);
            guns[player.gun_holding].sprite4.setScale(1, -1);

            player.body1.setScale(-1, 1);
            player.head2.setScale(1, -1);
            player.head3.setScale(-1, 1);
            player.body4.setScale(1, -1);

            player.hands[player.gun_holding].left1.setScale(-1, 1);
            player.hands[player.gun_holding].left2.setScale(1, -1);
            player.hands[player.gun_holding].left3.setScale(-1, 1);
            player.hands[player.gun_holding].left4.setScale(1, -1);

            player.hands[player.gun_holding].right1.setScale(-1, 1);
            player.hands[player.gun_holding].right2.setScale(1, -1);
            player.hands[player.gun_holding].right3.setScale(-1, 1);
            player.hands[player.gun_holding].right4.setScale(1, -1);
        }
        if ((Keyboard::isKeyPressed(Keyboard::W)||Keyboard::isKeyPressed(Keyboard::Space))&&isStanding)
        {
            player.position.speed_y-=player.jump_force*guns[player.gun_holding].swiftness;
        }


        if (isStanding)
        {
            player.body1.setTextureRect(IntRect(player.body_sprite_positionx[player.body_frame_counter], 0, 99, 99));
            player.body4.setTextureRect(IntRect(player.body_sprite_positionx[player.body_frame_counter], 0, 99, 99));
        }
        else
        {
            player.body1.setTextureRect(IntRect(300, 0, 100, 100));
            player.body4.setTextureRect(IntRect(300, 0, 100, 100));
        }

        window.draw(player.hands[player.gun_holding].left1);
        window.draw(player.hands[player.gun_holding].left2);
        window.draw(player.hands[player.gun_holding].left3);
        window.draw(player.hands[player.gun_holding].left4);

        window.draw(guns[player.gun_holding].sprite1);
        window.draw(guns[player.gun_holding].sprite2);
        window.draw(guns[player.gun_holding].sprite3);
        window.draw(guns[player.gun_holding].sprite4);

        window.draw(player.body1);
        window.draw(player.body2);
        window.draw(player.body3);
        window.draw(player.body4);

        window.draw(player.head1);
        window.draw(player.head2);
        window.draw(player.head3);
        window.draw(player.head4);



        window.draw(player.hands[player.gun_holding].right1);
        window.draw(player.hands[player.gun_holding].right2);
        window.draw(player.hands[player.gun_holding].right3);
        window.draw(player.hands[player.gun_holding].right4);*/

        health1=player.health;
        if (player.health>0)
        {
            health_text.setString(std::to_string(player.health));
            health.setScale((400*health1/player.max_health), 1);
        }
        else
        {
            health_text.setString("");
            health.setScale(0, 0);
        }
        window.draw(health);
        window.draw(health_text);


        isVictory=true;
        for (int i=0; i<types; i++)
        {
            for (int j=0; j<enemy[i][0].quantity; j++)
            {
                if (enemy[i][j].health>0/*&&victory_counter==120*/)
                isVictory=false;
            }
        }


        if (victory_counter<120||isVictory)
        {
            victory_counter--;
            if (isArena)
            {
                wave_string="Wave ";
                wave_string+=std::to_string(wave+2);
                wave_text.setString(wave_string);
                window.draw(wave_text);
            }
            else
            {
                window.draw(victory);
            }

        }
        if (player.health<=0)
        {
            for (int i=0; i<projectile_count; i++)
            {
                projectile[i].damage=0;
                projectile[i].time=0;
            }
            game_state=main_menu;
            isArena=false;
            music.stop();
            music.openFromFile("Sounds/music/menu.wav");
            music.play();
            player.deploy=guns[player.gun_holding].max_deploy;
            victory_counter=121;
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            for (int i=0; i<projectile_count; i++)
            {
                projectile[i].damage=0;
                projectile[i].time=0;
            }
            game_state=main_menu;
            isArena=false;
            music.stop();
            music.openFromFile("Sounds/music/menu.wav");
            music.play();
            player.deploy=guns[player.gun_holding].max_deploy;
            victory_counter=121;
        }



        if (victory_counter<=0)
        {
            if (isArena)
            {
                wave++;
                player.health=player.max_health;
                if (wave<max_waves)
                {
                    for (int i=0; i<types; i++)
                    {
                        for (int j=0; j<enemy[i][0].quantity; j++)
                        {
                            enemy[i][j].position=waves[wave].position[i][j];
                            enemy[i][j].health=waves[wave].health[i][j];
                            enemy[i][j].delay=enemy[i][j].max_delay;
                enemy[i][j].guns_delay=enemy[i][j].max_guns_delay;
                        }
                    }
                }
                else
                {
                    int temp=max_waves-1;
                    for (int i=0; i<types; i++)
                    {
                        for (int j=0; j<enemy[i][0].quantity; j++)
                        {
                            enemy[i][j].position=waves[temp].position[i][j];
                            enemy[i][j].health=waves[temp].health[i][j];
                            enemy[i][j].delay=enemy[i][j].max_delay;
                enemy[i][j].guns_delay=enemy[i][j].max_guns_delay;
                        }
                    }
                }

                //spawn
            }
            else
            {
                for (int i=0; i<projectile_count; i++)
                {
                    projectile[i].damage=0;
                    projectile[i].time=0;
                }
                game_state=main_menu;
                //isArena=false;
                music.stop();
                music.openFromFile("Sounds/music/menu.wav");
                music.play();
                player.deploy=guns[player.gun_holding].max_deploy;
            }
            victory_counter=121;
            isVictory=false;
        }

        guns[primary].icon.setPosition(1320, 900);
        guns[secondary].icon.setPosition(1520, 900);
        guns[special].icon.setPosition(1720, 900);

        window.draw(guns[primary].icon);
        window.draw(guns[secondary].icon);
        window.draw(guns[special].icon);

        if (guns[primary].ammo_used>0)
        {
            t="";
            t+=std::to_string(guns[primary].ammo);
            t+="/";
            t+=std::to_string(guns[primary].max_ammo);
            t1.setString(t);
            t1.setPosition(1320, 1020);
            window.draw(t1);
        }
        if (guns[secondary].ammo_used>0)
        {
            t="";
            t+=std::to_string(guns[secondary].ammo);
            t+="/";
            t+=std::to_string(guns[secondary].max_ammo);
            t1.setString(t);
            t1.setPosition(1520, 1020);
            window.draw(t1);
        }
        if (guns[special].ammo_used>0)
        {
            t="";
            t+=std::to_string(guns[special].ammo);
            t+="/";
            t+=std::to_string(guns[special].max_ammo);
            t1.setString(t);
            t1.setPosition(1720, 1020);
            window.draw(t1);
        }

        if (player.gun_holding==primary)
        {
            frame.setPosition(1315, 895);
        }
        else if (player.gun_holding==secondary)
        {
            frame.setPosition(1515, 895);
        }
        else
        {
            frame.setPosition(1715, 895);
        }
        window.draw(frame);

        guns[player.gun_holding].crosshair.setFrame(guns[player.gun_holding].delay);
        guns[player.gun_holding].crosshair.setPR(1, pos.x, pos.y, 0);
        window.draw(guns[player.gun_holding].crosshair.sprite);

    }



    else if (game_state==armory)
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            game_state=main_menu;
            scroll=0;
            if (category==0)
            {
                prechoice=primary;
            }
            else if (category==1)
            {
                prechoice=secondary;
            }
            else if (category==2)
            {
                prechoice=special;
            }
            else if (category==3)
            {
                prechoice=passive;
            }
        }

        window.draw(menu);


        primary_button.texture1=guns[primary].icon_texture;
        secondary_button.texture1=guns[secondary].icon_texture;
        special_button.texture1=guns[special].icon_texture;
        passive_button.texture1=passive_texture[passive];


        primary_button.texture2=guns[primary].icon_texture;
        secondary_button.texture2=guns[secondary].icon_texture;
        special_button.texture2=guns[special].icon_texture;
        passive_button.texture2=passive_texture[passive];




        if (primary_button.isPointed(pos))
        {
            primary_button.expand();
            if (isReleased)
            {
                category=0;
                prechoice=primary;
                scroll=0;
            }
        }
        else
        {
            primary_button.shrink();
        }

        if (secondary_button.isPointed(pos))
        {
            secondary_button.expand();
            if (isReleased)
            {
                category=1;
                prechoice=secondary;
                scroll=0;
            }
        }
        else
        {
            secondary_button.shrink();
        }

        if (special_button.isPointed(pos))
        {
            special_button.expand();
            if (isReleased)
            {
                category=2;
                prechoice=special;
                scroll=0;
            }
        }
        else
        {
            special_button.shrink();
        }

        if (passive_button.isPointed(pos))
        {
            passive_button.expand();
            if (isReleased)
            {
                category=3;
                prechoice=passive;
                scroll=0;
            }
        }
        else
        {
            passive_button.shrink();
        }







        if (category==0)
        {
            primary_button.expand();
            for (int i=0; i<guns_count; i++)
            {
                if (guns[i].cat==0)
                {
                    if (guns[i].y-scroll>-150&&guns[i].y-scroll<1230)
                    {
                        if (IntRect(guns[i].x, guns[i].y-scroll, 100, 100).contains(pos)&&isReleased)
                        {
                            prechoice=i;
                        }





                        guns[i].icon.setPosition(guns[i].x, guns[i].y-scroll);
                        window.draw(guns[i].icon);


                    }
                }
            }
            frame.setPosition(guns[prechoice].x-5, guns[prechoice].y-5-scroll);
            window.draw(frame);
            player.body.sprite.setTexture(player.idle);
            guns[prechoice].animation.setFrame(0);
            guns[prechoice].left.setFrame(0);
            guns[prechoice].right.setFrame(0);
            player.head.setPos(0.1);

            player.body.setPR(1, 1780, 400, 0);
            guns[prechoice].animation.setPR(1, 1780, 400, 0);
            guns[prechoice].left.setPR(1, 1780, 400, 0);
            guns[prechoice].right.setPR(1, 1780, 400, 0);
            player.head.setPR(1, 1780, 400, 0);
            window.draw(guns[prechoice].left.sprite);
            window.draw(guns[prechoice].animation.sprite);
            window.draw(player.body.sprite);
            window.draw(player.head.sprite);
            window.draw(guns[prechoice].right.sprite);



            text.setString(guns[prechoice].temp);

            window.draw(text);

            window.draw(equipped);

            if (prechoice!=primary)
            {
                if (equip.isPointed(pos))
                {
                    equip.expand();
                    if (isReleased)
                    {
                        primary=prechoice;
                    }
                }
                else
                {
                    equip.shrink();
                }
                window.draw(equip.sprite);
            }

        }
        else if (category==1)
        {
            secondary_button.expand();
            //primary_button.expand();
            for (int i=0; i<guns_count; i++)
            {
                if (guns[i].cat==1)
                {
                    if (guns[i].y-scroll>-150&&guns[i].y-scroll<1230)
                    {
                        if (IntRect(guns[i].x, guns[i].y-scroll, 100, 100).contains(pos)&&isReleased)
                        {
                            prechoice=i;
                        }





                        guns[i].icon.setPosition(guns[i].x, guns[i].y-scroll);
                        window.draw(guns[i].icon);


                    }
                }
            }
            frame.setPosition(guns[prechoice].x-5, guns[prechoice].y-5-scroll);
            window.draw(frame);
            player.body.sprite.setTexture(player.idle);
            guns[prechoice].animation.setFrame(0);
            guns[prechoice].left.setFrame(0);
            guns[prechoice].right.setFrame(0);
            player.head.setPos(0.1);

            player.body.setPR(1, 1780, 400, 0);
            guns[prechoice].animation.setPR(1, 1780, 400, 0);
            guns[prechoice].left.setPR(1, 1780, 400, 0);
            guns[prechoice].right.setPR(1, 1780, 400, 0);
            player.head.setPR(1, 1780, 400, 0);
            window.draw(guns[prechoice].left.sprite);
            window.draw(guns[prechoice].animation.sprite);
            window.draw(player.body.sprite);
            window.draw(player.head.sprite);
            window.draw(guns[prechoice].right.sprite);



            text.setString(guns[prechoice].temp);

            window.draw(text);

            window.draw(equipped);

            if (prechoice!=secondary)
            {
                if (equip.isPointed(pos))
                {
                    equip.expand();
                    if (isReleased)
                    {
                        secondary=prechoice;
                    }
                }
                else
                {
                    equip.shrink();
                }
                window.draw(equip.sprite);
            }

        }
        else if (category==2)
        {
            special_button.expand();
            //primary_button.expand();
            for (int i=0; i<guns_count; i++)
            {
                if (guns[i].cat==2)
                {
                    if (guns[i].y-scroll>-150&&guns[i].y-scroll<1230)
                    {
                        if (IntRect(guns[i].x, guns[i].y-scroll, 100, 100).contains(pos)&&isReleased)
                        {
                            prechoice=i;
                        }





                        guns[i].icon.setPosition(guns[i].x, guns[i].y-scroll);
                        window.draw(guns[i].icon);


                    }
                }
            }
            frame.setPosition(guns[prechoice].x-5, guns[prechoice].y-5-scroll);
            window.draw(frame);
            player.body.sprite.setTexture(player.idle);
            guns[prechoice].animation.setFrame(0);
            guns[prechoice].left.setFrame(0);
            guns[prechoice].right.setFrame(0);
            player.head.setPos(0.1);

            player.body.setPR(1, 1780, 400, 0);
            guns[prechoice].animation.setPR(1, 1780, 400, 0);
            guns[prechoice].left.setPR(1, 1780, 400, 0);
            guns[prechoice].right.setPR(1, 1780, 400, 0);
            player.head.setPR(1, 1780, 400, 0);
            window.draw(guns[prechoice].left.sprite);
            window.draw(guns[prechoice].animation.sprite);
            window.draw(player.body.sprite);
            window.draw(player.head.sprite);
            window.draw(guns[prechoice].right.sprite);



            text.setString(guns[prechoice].temp);

            window.draw(text);

            window.draw(equipped);

            if (prechoice!=special)
            {
                if (equip.isPointed(pos))
                {
                    equip.expand();
                    if (isReleased)
                    {
                        special=prechoice;
                    }
                }
                else
                {
                    equip.shrink();
                }
                window.draw(equip.sprite);
            }

        }
        else if (category==3)
        {
            passive_button.expand();

            for (int i=0; i<2; i++)
            {

                if (passive_y[i]-scroll>-150&&passive_y[i]-scroll<1230)
                {
                    if (IntRect(passive_x[i], passive_y[i]-scroll, 100, 100).contains(pos)&&isReleased)
                    {
                        prechoice=i;
                    }





                    passive_icon.setTexture(passive_texture[i]);
                    passive_icon.setPosition(passive_x[i], passive_y[i]-scroll);
                    window.draw(passive_icon);


                }

            }
            frame.setPosition(passive_x[prechoice]-5, passive_y[prechoice]-5-scroll);
            window.draw(frame);
            player.body.sprite.setTexture(player.idle);
            guns[primary].animation.setFrame(0);
            guns[primary].left.setFrame(0);
            guns[primary].right.setFrame(0);
            player.head.setPos(0.1);

            player.body.setPR(1, 1780, 400, 0);
            guns[primary].animation.setPR(1, 1780, 400, 0);
            guns[primary].left.setPR(1, 1780, 400, 0);
            guns[primary].right.setPR(1, 1780, 400, 0);
            player.head.setPR(1, 1780, 400, 0);

            window.draw(guns[primary].left.sprite);
            window.draw(guns[primary].animation.sprite);
            window.draw(player.body.sprite);
            window.draw(player.head.sprite);
            window.draw(guns[primary].right.sprite);



            //text.setString(guns[prechoice].temp);

            window.draw(passive_text[prechoice]);

            window.draw(equipped);

            if (prechoice!=passive)
            {
                if (equip.isPointed(pos))
                {
                    equip.expand();
                    if (isReleased)
                    {
                        if (prechoice==0)
                        {
                            player.max_health=144;
                            player.max_speed=20;
                        }
                        else if (prechoice==1)
                        {
                            player.max_health=120;
                            player.max_speed=30;
                        }
                        passive=prechoice;

                    }
                }
                else
                {
                    equip.shrink();
                }
                window.draw(equip.sprite);
            }


        }

        window.draw(primary_button.sprite);
        window.draw(secondary_button.sprite);
        window.draw(special_button.sprite);
        window.draw(passive_button.sprite);

        /*

        guns[primary].icon.setPosition(910, 640);
        guns[secondary].icon.setPosition(710, 640);
        guns[special].icon.setPosition(1110, 640);



        if (IntRect(910, 640, 100, 100).contains(Mouse::getPosition(window))&&Mouse::isButtonPressed(Mouse::Left))
        {
            text.setString(guns[primary].temp);
            game_state=stats;
        }

        if (IntRect(710, 640, 100, 100).contains(Mouse::getPosition(window))&&Mouse::isButtonPressed(Mouse::Left))
        {
            text.setString(guns[secondary].temp);
            game_state=stats;
        }

        if (IntRect(1110, 640, 100, 100).contains(Mouse::getPosition(window))&&Mouse::isButtonPressed(Mouse::Left))
        {
            text.setString(guns[special].temp);
            game_state=stats;
        }

        window.draw(guns[primary].icon);
        window.draw(guns[secondary].icon);
        window.draw(guns[special].icon);
        window.draw(passive_icon);

        //arrow_button.setPosition(810, 340);
        //arrow_button.setScale(1, 1);



        if (arrow_button[0].isPointed(pos))
        {
            arrow_button[0].expand();
            if (isReleased)
            {
                if (passive==0)
                {
                    passive=1;
                    player.max_health=120;
                    player.max_speed=30;
                    passive_icon.setTexture(passive_texture[passive]);
                }
                else if (passive==1)
                {
                    passive=0;
                    player.max_health=144;
                    player.max_speed=20;
                    passive_icon.setTexture(passive_texture[passive]);
                }
            }
        }
        else
        {
            arrow_button[0].shrink();
        }
        window.draw(arrow_button[0].sprite);

        //arrow_button.setPosition(810, 240);
        //arrow_button.setScale(1, -1);
        if (arrow_button[1].isPointed(pos))
        {
            arrow_button[1].expand();
            if (isReleased)
            {
                if (passive==0)
                {
                    passive=1;
                     player.max_health=120;
                    player.max_speed=30;
                    passive_icon.setTexture(passive_texture[passive]);
                }
                else if (passive==1)
                {
                    passive=0;
                     player.max_health=144;
                    player.max_speed=20;
                    passive_icon.setTexture(passive_texture[passive]);
                }
            }
        }
        else
        {
            arrow_button[1].shrink();
        }
        window.draw(arrow_button[1].sprite);

        //arrow_button.setPosition(910, 740);
        //arrow_button.setScale(1, 1);.health=
        if (arrow_button[2].isPointed(pos))
        {
            arrow_button[2].expand();
            if (isReleased)
            {
                if (primary==0)
                {
                    primary=3;
                }
                else if (primary==3)
                {
                    primary=7;
                }

                else if (primary==7)
                {
                    primary=11;
                }
                else if (primary==11)
                {
                    primary=12;
                }
                else if (primary==12)
                {
                    primary=16;
                }
                else if (primary==16)
                {
                    primary=20;
                }
                else if (primary==20)
                {
                    primary=21;
                }
                else if (primary==21)
                {
                    primary=24;
                }
                else if (primary==24)
                {
                    primary=27;
                }
                else if (primary==27)
                {
                    primary=0;
                }
                player.deploy=guns[primary].max_deploy;
            }
        }
        else
        {
            arrow_button[2].shrink();
        }
        window.draw(arrow_button[2].sprite);

        //arrow_button.setPosition(710, 740);
        //arrow_button.setScale(1, 1);
        if (arrow_button[3].isPointed(pos))
        {
            arrow_button[3].expand();
            if (isReleased)
            {
              if (secondary==1)
                {
                    secondary=5;
                }
                else if (secondary==5)
                {
                    secondary=6;
                }
                else if (secondary==6)
                {
                    secondary=9;
                }
                else if (secondary==9)
                {
                    secondary=10;
                }
                else if (secondary==10)
                {
                    secondary=15;
                }
                else if (secondary==15)
                {
                    secondary=19;
                }
                else if (secondary==19)
                {
                    secondary=22;
                }
                else if (secondary==22)
                {
                    secondary=26;
                }
                else if (secondary==26)
                {
                    secondary=28;
                }
                else if (secondary==28)
                {
                    secondary=29;
                }
                else if (secondary==29)
                {
                    secondary=34;
                }
                else if (secondary==34)
                {
                    secondary=1;
                }
            }

        }
        else
        {
            arrow_button[3].shrink();
        }
        window.draw(arrow_button[3].sprite);



        if (arrow_button[4].isPointed(pos))
        {
            arrow_button[4].expand();
            if (isReleased)
            {
                if (special==2)
                {
                    special=4;
                }
                else if (special==4)
                {
                    special=8;
                }
                else if (special==8)
                {
                    special=13;
                }
                else if (special==13)
                {
                    special=14;
                }
                else if (special==14)
                {
                    special=17;
                }
                else if (special==17)
                {
                    special=18;
                }
                else if (special==18)
                {
                    special=23;
                }
                else if (special==23)
                {
                    special=25;
                }
                else if (special==25)
                {
                    special=30;
                }
                else if (special==30)
                {
                    special=31;
                }
                else if (special==31)
                {
                    special=32;
                }
                else if (special==32)
                {
                    special=33;
                }
                else if (special==33)
                {
                    special=35;
                }
                else if (special==35)
                {
                    special=2;
                }
            }
        }
        else
        {
            arrow_button[4].shrink();
        }
        window.draw(arrow_button[4].sprite);



        if (arrow_button[5].isPointed(pos))
        {
            arrow_button[5].expand();
            if (isReleased)
            {
                if (primary==7)
                {
                    primary=3;
                }
                else if (primary==3)
                {
                    primary=0;
                }
                else if (primary==0)
                {
                    primary=27;
                }
                else if (primary==27)
                {
                    primary=24;
                }
                else if (primary==24)
                {
                    primary=21;
                }
                else if (primary==21)
                {
                    primary=20;
                }
                else if (primary==20)
                {
                    primary=16;
                }
                else if (primary==16)
                {
                    primary=12;
                }
                else if (primary==12)
                {
                    primary=11;
                }
                else if (primary==11)
                {
                    primary=7;
                }
                player.deploy=guns[primary].max_deploy;
            }
        }
        else
        {
            arrow_button[5].shrink();
        }
        window.draw(arrow_button[5].sprite);


        if (arrow_button[6].isPointed(pos))
        {
            arrow_button[6].expand();
            if (isReleased)
            {
                if (secondary==9)
                {
                    secondary=6;
                }
                else if (secondary==6)
                {
                    secondary=5;
                }
                 else if (secondary==5)
                {
                    secondary=1;
                }
                else if (secondary==1)
                {
                    secondary=34;
                }
                else if (secondary==34)
                {
                    secondary=29;
                }
                else if (secondary==29)
                {
                    secondary=28;
                }
                else if (secondary==28)
                {
                    secondary=26;
                }
                else if (secondary==26)
                {
                    secondary=22;
                }
                else if (secondary==22)
                {
                    secondary=19;
                }
                else if (secondary==19)
                {
                    secondary=15;
                }
                else if (secondary==15)
                {
                    secondary=10;
                }
                else if (secondary==10)
                {
                    secondary=9;
                }


            }
        }
        else
        {
            arrow_button[6].shrink();
        }
        window.draw(arrow_button[6].sprite);


        if (arrow_button[7].isPointed(pos))
        {
            arrow_button[7].expand();
            if (isReleased)
            {
                if (special==14)
                {
                    special=13;
                }
                else if (special==13)
                {
                    special=8;
                }
                else if (special==8)
                {
                    special=4;
                }
                else if (special==4)
                {
                    special=2;
                }
                else if (special==2)
                {
                    special=35;
                }
                else if (special==33)
                {
                    special=32;
                }
                else if (special==32)
                {
                    special=31;
                }
                else if (special==31)
                {
                    special=30;
                }
                else if (special==30)
                {
                    special=25;
                }
                else if (special==25)
                {
                    special=23;
                }
                else if (special==23)
                {
                    special=18;
                }
                else if (special==18)
                {
                    special=17;
                }
                else if (special==17)
                {
                    special=14;
                }
                else if (special==35)
                {
                    special=33;
                }


            }
        }
        else
        {
            arrow_button[7].shrink();
        }
        window.draw(arrow_button[7].sprite);
        */
    }
    if (game_state==comics)
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            game_state=main_menu;
        }

        if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            game_state=choice;
        }
        window.draw(comic);
    }




    /*if (game_state==stats)
    {
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            game_state=main_menu;
        }
        window.draw(menu);
        window.draw(text);
    }*/

    //crosshair.setPosition(pos.x-50, pos.y-50);
    //window.draw(crosshair);
    if (hitstate==1)
    {
        markers.setTexture(hitmarkers);
        markers.setPosition(pos.x-50, pos.y-50);
        window.draw(markers);

    }
    else if (hitstate==2)
    {
        markers.setTexture(killmarkers);
        markers.setPosition(pos.x-50, pos.y-50);
        window.draw(markers);

    }
    window.display();
    }
}
//.health=
