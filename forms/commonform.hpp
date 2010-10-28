#ifndef COMMONFORM_HPP
#define COMMONFORM_HPP

class CommonForm {
public:
    virtual void guardar() = 0;
protected:
    bool isSaved;
};

#endif // COMMONFORM_HPP
