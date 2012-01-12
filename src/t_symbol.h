#ifndef T_SYMBOL_H
#define T_SYMBOL_H

#include <vector>
#include <string>
#include <QtCore/QLine>
#include <QtCore/QPoint>
#include <QtCore/QRect>
#include <cstdint>

class t_wireObject;
class t_pinObject;
class t_symbolObject;
class t_component;
class t_component_field;
class t_xyPair;

#define MOVE 1
#define WIRE 2
#define PIN  4
#define INFO 8

#define DRAW_PINNUMBER 1
#define DRAW_PINNAME 2
#define UNITS_LOCKED 3
#define OPTION_FLAG 4

#define TEXT_ORIENT 1
#define VISIBLE 2
#define ITALIC 3
#define BOLD 4

class t_library
{
    public:
        void                            load(const std::string &fileToRead);
        std::string                     fileName;
        uint8_t                         majorVersion, minorVersion;
        std::vector<t_component*>       components;
    private:
        bool                            checkVersion(const std::string &line);

};

class t_component
{
    public:
        std::string                     name;
        std::string                     reference;
        uint16_t                        text_offset;
        uint8_t                         unit_count;
        uint8_t                         flags;
        std::vector<t_component_field>  fields;
        std::vector<std::string>        fplist;
        std::vector<t_symbolObject*>    items;
        bool                            loadDEF(const std::string &line);
        bool                            loadF(const std::string &line);
        void                            addFPlist(const std::string &line);
        bool                            addItem(const std::string &line);
};

class t_component_field
{
    public:
        uint16_t                        fieldNo;
        std::string                     name;
        int16_t                         posx, posy;
        uint16_t                        text_size;
        uint8_t                         flags;
        char                            htext_justify, vtext_justify;
        bool                            loadFields(const std::string &line);
};

class t_symbolObject
{
    public:
        int16_t posx, posy;
        uint16_t unit, convert, thickness;
        char fill;
        uint8_t type;
        virtual QRect rect(void) const = 0;
};

class t_CircleObject : public t_symbolObject
{
    public:
        t_CircleObject(const std::string &data);
        uint16_t radius;
        QRect rect(void) const;
};

class t_PolylineObject : public t_symbolObject
{
    public:
        t_PolylineObject(const std::string &data);
        uint16_t point_count;
        std::vector<t_xyPair> points;
        QRect rect(void) const;
};

class t_PinObject : public t_symbolObject
{
    public:
        t_PinObject(const std::string &data);
        std::string name, num;
        uint16_t length, name_text_size, num_text_size;
        char direction, electrical_type, pin_type;
        QRect rect(void) const;
};

class t_RectangleObject : public t_symbolObject
{
    public:
        t_RectangleObject(const std::string &data);
        int16_t endx, endy;
        QRect rect(void) const;
};

class t_ArcObject : public t_symbolObject
{
    public:
        t_ArcObject(const std::string &data);
        int16_t radius;
        int32_t start_angle, end_angle, endx, endy, startx, starty;
        QRect rect(void) const;
};

class t_xyPair
{
    public:
        int16_t x, y;
};
#endif
