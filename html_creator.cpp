#include "html_creator.h"

QString HTML_Creator::toHTML(const Word *word){
    if(!word) return QString();
    // heading
    QString res="<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">"
                "p, li { white-space: pre-wrap; }"
                "hr { height: 1px; border-width: 0; }"
                "li.unchecked::marker { content: \"\2610\"; }"
                "li.checked::marker { content: \"\2612\"; }"
                "</style></head>"
                "<body style=\" font-family:'Comfortaa'; font-size:13pt; font-weight:400; font-style:normal;\">";


    // The word itself
    res+=QString(
               "<p align=\"center\" "
               "style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
               "<span style=\" font-size:18pt; font-weight:1000; color:#414699;\">"
               "%1"
               "</span></p>"
                ).arg(QString::fromStdString(word->word));

    for(int i=0, cnt=0; i<POS::Count; i++)
        if(!word->def[i].empty()){
            res+="<br>";
            res+=QString(
               "<p align=\"left\" "
               "style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
               "<span style=\" font-size:14pt; font-weight:700; color:#414699;\">"
               "%1. %2: "
               "</span></p>"
                       ).arg(QString::number(++cnt),QString::fromStdString(POS::TypeString[i]));
            for(const std::string& def: word->def[i])
                res+=QString(
                   "<p align=\"justify\" "
                   "style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
                   "<span style=\" font-size:14pt; font-weight:700; color:#414699;\">"
                   "    - %1"
                   "</span></p>"
                           ).arg(QString::fromStdString(def));
        }

    // ending
    res+="</body></html>";
    return res;
}
