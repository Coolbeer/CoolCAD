#include "t_symbol.h"

#include <boost/lexical_cast.hpp>
#include <fstream>
#include <string>
#include <iostream>

#include "pwanstrings.h"

//Ripped out of kicad sources
#define NORMALIZE_ANGLE_POS( Angle )\
{                                   \
    while( Angle < 0 )              \
        Angle += 3600;              \
    while(Angle >= 3600)            \
        Angle -= 3600;              \
}                                       

void t_library::load(const std::string &fileToRead)
{
    std::ifstream inFile;
    std::string line;
    bool haveDef;
    t_component *tmpComp;
    inFile.open(fileToRead, std::ios::in);

    if(!inFile.is_open())
        return;

    std::cout << "File Open\n";
    std::getline(inFile, line);
    if(!checkVersion(line))
        return;

    std::cout << "Version OK\n";

    while(true)
    {
        std::getline(inFile, line);
        if(line[0] == '#')
        {
//            std::cout << "Comment\n";
        }
        else if(line[0] == 'D' && line[1] == 'E' && line[2] == 'F')
        {
//            std::cout << "DEF\n";
            haveDef = true;
            tmpComp = new t_component;
            tmpComp->loadDEF(line);
        }
        else if(line[0] == 'F' && haveDef)
        {
//            std::cout << "F\n";
            tmpComp->loadF(line);
        }
        else if(line.substr(0,7) == "$FPLIST")
        {
//            std::cout << "fplist\n";
            while(1)
            {
                std::getline(inFile, line);
                if(line == "$ENDFPLIST")
                {
//                    std::cout << "endfplist\n";
                    break;
                }
                tmpComp->addFPlist(line);
//                std::cout << line << "\n";
            }
        }
        else if(line == "DRAW")
        {
//            std::cout << "DRAW\n";
            while(1)
            {
                std::getline(inFile, line);
                if(line == "ENDDRAW")
                {
//                    std::cout << "ENDDRAW\n";
                    break;
                }
                tmpComp->addItem(line);
            }
        }
        else if(line == "ENDDEF")
            components.push_back(tmpComp);
        if(inFile.eof())
            break;
    }
    inFile.close();
}

bool t_library::checkVersion(const std::string &line)
{
    std::vector<std::string> expLine = pwan::strings::explode(line);
    if(expLine.at(0) != "EESchema-LIBRARY")
        return false;
    if(expLine.at(2) != "2.3")
        return false;
    return true;
}

bool t_component_field::loadFields(const std::string &line)
{
    std::vector<std::string> expLine = pwan::strings::explode(line);
    if(expLine.at(0).at(0) != 'F')
        return false;

    fieldNo = boost::lexical_cast<uint16_t>(expLine.at(0).substr(1));
//    std::cout << fieldNo << "\n";

    name = expLine.at(1);
//    std::cout << name << "\n";

    posx = boost::lexical_cast<int16_t>(expLine.at(2));
//    std::cout << posx << "\n";

    posy = boost::lexical_cast<int16_t>(expLine.at(3)) * -1;
//    std::cout << posy << "\n";

    text_size = boost::lexical_cast<uint16_t>(expLine.at(4));
//    std::cout << text_size << "\n";

    if(expLine.at(5) == "V")
        flags |= (1 << TEXT_ORIENT);
    if(expLine.at(6) == "V")
        flags |= (1 << VISIBLE);
    htext_justify = expLine.at(7).at(0);
    vtext_justify = expLine.at(8).at(0);
    if(expLine.at(8).at(1) == 'I')
        flags |= (1 << ITALIC);
    if(expLine.at(8).at(2) == 'B')
        flags |= (1 << BOLD);
    return true;
}

bool t_component::loadDEF(const std::string &line)
{
    std::vector<std::string> expLine = pwan::strings::explode(line);
    if(expLine.at(0) != "DEF")
        return false;
    name = expLine.at(1);
    reference = expLine.at(2);
    text_offset = boost::lexical_cast<uint16_t>(expLine.at(4));
    if(expLine.at(5) == "Y")
        flags |= (1 << DRAW_PINNUMBER);
    if(expLine.at(6) == "Y")
        flags |= (1 << DRAW_PINNAME);
    unit_count = boost::lexical_cast<uint8_t>(expLine.at(7));
    if(expLine.at(8) == "L")
        flags |= (1 << UNITS_LOCKED);
    if(expLine.at(9) == "P")
        flags |= (1 << OPTION_FLAG);
    return true;
}

bool t_component::loadF(const std::string &line)
{
    t_component_field tmp_field;
    bool returnValue = tmp_field.loadFields(line);
    fields.push_back(tmp_field);
    return returnValue;
}

void t_component::addFPlist(const std::string &line)
{
    fplist.push_back(line);
}

bool t_component::addItem(const std::string &line)
{
    if(line.at(0) == 'C')
    {
//        std::cout << "circle\n";
        t_CircleObject *circleObject = new t_CircleObject(line);
        items.push_back(circleObject);
    }
    else if(line.at(0) == 'P')
    {
//        std::cout << "polygon\n";
        t_PolylineObject *polylineObject = new t_PolylineObject(line);
        items.push_back(polylineObject);
    }
    else if(line.at(0) == 'X')
    {
//        std::cout << "Pin\n";
        t_PinObject *pinObject = new t_PinObject(line);
        items.push_back(pinObject);
    }
    else if(line.at(0) == 'S')
    {
//        std::cout << "Rectangle\n";
        t_RectangleObject *rectangleObject = new t_RectangleObject(line);
        items.push_back(rectangleObject);
    }
    else if(line.at(0) == 'A')
    {
//        std::cout << "Arc\n";
        t_ArcObject *arcObject = new t_ArcObject(line);
        items.push_back(arcObject);
    }

    else
        return false;
    return true;
}

t_CircleObject::t_CircleObject(const std::string &line)
{
    std::vector<std::string> expLine = pwan::strings::explode(line);
    if(expLine.at(0) != "C")
        return;

    type = 'C';
    posx = boost::lexical_cast<int16_t>(expLine.at(1));
    posy = boost::lexical_cast<int16_t>(expLine.at(2))*-1;
    radius = boost::lexical_cast<uint16_t>(expLine.at(3));
    unit = boost::lexical_cast<uint16_t>(expLine.at(4));
    convert = boost::lexical_cast<uint16_t>(expLine.at(5));
    thickness = boost::lexical_cast<uint16_t>(expLine.at(6));
    fill = expLine.at(7).at(0);
}

QRect t_CircleObject::rect(void) const
{
    return (QRect(posx-radius, posy-radius, radius*2, radius*2));
}

t_PolylineObject::t_PolylineObject(const std::string &data)
{
    std::vector<std::string> expLine = pwan::strings::explode(data);
    if(expLine.at(0) != "P")
        return;

    type = 'P';
    point_count = boost::lexical_cast<uint16_t>(expLine.at(1));
    unit = boost::lexical_cast<uint16_t>(expLine.at(2));
    convert = boost::lexical_cast<uint16_t>(expLine.at(3));
    thickness = boost::lexical_cast<uint16_t>(expLine.at(4));

    for(uint16_t i = 0; i != point_count; ++i)
    {
        t_xyPair xyPair;
        xyPair.x = boost::lexical_cast<int16_t>(expLine.at(5+(i*2)));
        xyPair.y = boost::lexical_cast<int16_t>(expLine.at(6+(i*2))) * -1;

        points.push_back(xyPair);
     }
    fill = expLine.at(7+((point_count-1) *2)).at(0);
}

QRect t_PolylineObject::rect(void) const
{
    int16_t topX, topY, bottomX, bottomY;
    topX = topY = bottomX = bottomY = 0;
    for(uint16_t i = 0; i != point_count; ++i)
    {
        if(points.at(i).x < topX)
            topX = points.at(i).x;
        else if(points.at(i).x > bottomX)
            bottomX = points.at(i).x;
        if(points.at(i).y < topY)
            topY = points.at(i).y;
        else if(points.at(i).y > bottomY)
            bottomY = points.at(i).y;
    }
    return (QRect(QPoint(topX, topY), QPoint(bottomX, bottomY)));
}

t_PinObject::t_PinObject(const std::string &data)
{
    std::vector<std::string> expLine = pwan::strings::explode(data);
    if(expLine.at(0) != "X")
        return;

    type = 'X';
    name = expLine.at(1);
    num = expLine.at(2);
    posx = boost::lexical_cast<int16_t>(expLine.at(3));
    posy = boost::lexical_cast<int16_t>(expLine.at(4))*-1;
    length = boost::lexical_cast<uint16_t>(expLine.at(5));
    direction = expLine.at(6).at(0);
    name_text_size = boost::lexical_cast<uint16_t>(expLine.at(7));
    num_text_size = boost::lexical_cast<uint16_t>(expLine.at(8));
    electrical_type = expLine.at(9).at(0);
    pin_type = expLine.at(10).at(0);
}

QRect t_PinObject::rect(void) const
{
    return (QRect(QPoint(posx, posy), QPoint(posx, posy)));
}

t_RectangleObject::t_RectangleObject(const std::string &data)
{
    std::vector<std::string> expLine = pwan::strings::explode(data);
    if(expLine.at(0) != "S")
        return;

    type = 'S';
    posx = boost::lexical_cast<int16_t>(expLine.at(1));
    posy = boost::lexical_cast<int16_t>(expLine.at(2))*-1;
    endx = boost::lexical_cast<int16_t>(expLine.at(3));
    endy = (boost::lexical_cast<int16_t>(expLine.at(4))*-1);
    unit = boost::lexical_cast<uint16_t>(expLine.at(5));
    convert = boost::lexical_cast<uint16_t>(expLine.at(6));
    thickness = boost::lexical_cast<uint16_t>(expLine.at(7));
    fill = expLine.at(8).at(0);
}

QRect t_RectangleObject::rect(void) const
{
    int16_t topLx, topLy, botRx, botRy;
    if(endx < posx)
    {
        topLx = endx;
        botRx = posx;
    }
    else
    {
        topLx = posx;
        botRx = endx;
    }
    if(endy < posy)
    {
        topLy = endy;
        botRy = posx;
    }
    else
    {
        topLy = posy;
        botRy = endy;
    }
    return (QRect(QPoint(topLx, topLy), QPoint(botRx, botRy)));
}

t_ArcObject::t_ArcObject(const std::string &data)
{
    std::vector<std::string> expLine = pwan::strings::explode(data);
    if(expLine.at(0) != "A")
        return;

    type = 'A';
    posx = boost::lexical_cast<int16_t>(expLine.at(1));
    posy = boost::lexical_cast<int16_t>(expLine.at(2))*-1;
    radius = boost::lexical_cast<int16_t>(expLine.at(3));
    start_angle = boost::lexical_cast<int32_t>(expLine.at(4));
    NORMALIZE_ANGLE_POS(start_angle);
    start_angle = (start_angle << 4) / 10;
    end_angle = boost::lexical_cast<int32_t>(expLine.at(5));
    NORMALIZE_ANGLE_POS(end_angle);
    end_angle = ((end_angle << 4) / 10) - start_angle;
    unit = boost::lexical_cast<uint16_t>(expLine.at(6));
    convert = boost::lexical_cast<uint16_t>(expLine.at(7));
    thickness = boost::lexical_cast<uint16_t>(expLine.at(8));
    fill = expLine.at(9).at(0);
    startx = boost::lexical_cast<int16_t>(expLine.at(10));
    starty = boost::lexical_cast<int16_t>(expLine.at(11))*-1;
    endx = boost::lexical_cast<int16_t>(expLine.at(12)) - posx;
    endy = (boost::lexical_cast<int16_t>(expLine.at(13))*-1) - posy;
}

QRect t_ArcObject::rect(void) const
{
    return (QRect());
}
