#include "laser_cutting_module.h"
#include "math.h"
#include "QtMath"

laser_cutting_module::laser_cutting_module(QWidget *parent)
    : base_public_widget(parent)
{
    InitData();
    QPalette canvasPallette = palette();
    canvasPallette.setColor(LABEL_TEXT_COLOR_GREEN);
    canvasPallette.setColor(WIDGET_WINDOW_COLOR_BLACK);

    /*
    QLabel *canvalLabel = new QLabel(this);
    canvalLabel->setAutoFillBackground(true);
    canvalLabel->setPixmap(QPixmap(":/icons/iphonePic.png"));
    canvalLabel->setScaledContents(true);
    canvalLabel->setGeometry(0,0,600,660);
    canvalLabel->hide();
    */

    laserTrajModePtr = new laser_trajectory_module(this);
    laserTrajModePtr->setAutoFillBackground(true);
    laserTrajModePtr->setGeometry(0,0,600,660);

    // creat function button
    funcBtnGrp = new QButtonGroup(this);
    funcBtnGrp->setExclusive(true);

    for(int i = 0; i < MAX_FUNC_BTN_NUM; i++)
    {
        funcBtn[i] = new QPushButton(this);
        funcBtn[i]->setFont(QFont(HMI_COMMON_FONT_SIZE_10));
        funcBtn[i]->setGeometry(i*100,660 ,100,45);
        funcBtn[i]->setAutoExclusive(true);
        funcBtn[i]->setCheckable(true);
        funcBtnGrp->addButton(funcBtn[i]);
    }
    funcBtn[0]->setChecked(true);
    funcBtn[0]->setText(tr("加工模式"));
    funcBtn[1]->setText(tr("抓靶设定"));
    funcBtn[2]->setText(tr("机台设定"));
    funcBtn[3]->setText(tr("偏位校正"));
    funcBtn[4]->setText(tr("振镜校正"));
    funcBtn[5]->setText(tr("相机校正"));

    // creat function button slot mapping
    connect(funcBtnGrp, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(SlotBtnFunction(QAbstractButton*)));

    // 测试读取dxf格式文件
    char dxfilestr[255] = "testdxf.dxf";
    ReadDxfFile(dxfilestr);

    // 获取设定显示有图矩形范围
    const double trajMartin = 10;
    double ltx = entityGraph.getCoordMinX() - trajMartin;
    double lty = entityGraph.getCoordMinY() - trajMartin;
    double rbx = entityGraph.getCoordMaxX() + trajMartin;
    double rby = entityGraph.getCoordMaxY() + trajMartin;

    laserTrajModePtr->frameTraj(ltx, lty, rbx, rby);
    laserTrajModePtr->paintDxfTraj(entityGraph.topDataVectorPtr);

    WriteXml("testdxf.xml");

    setPalette(canvasPallette);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFocusPolicy(Qt::StrongFocus);
    setAutoFillBackground(true);
    resize(660,660 + 5 + 40);

}
void laser_cutting_module::UpdateData(void)
{
    //qDebug()<<"[HMI](alarm_module)--UpdateData()!";
    UpdateCuttingFunction();
}
void laser_cutting_module::Respond_operate(int, bool)
{
    qDebug()<<"[HMI](alarm_module)--Respond_operate()!";
}
void laser_cutting_module::Refresh_button_text(int, const QString &)
{
    qDebug()<<"[HMI](alarm_module)--Refresh_button_text()!";
}
void laser_cutting_module::InitData(void)
{
    curFuncFlag = CUTTING_MODE;
    // Init every laser cutting technology from file
    laserGrp[0].power = 10;
    laserGrp[0].freq = 10000;
    laserGrp[0].duty = 0.5;
}
void laser_cutting_module::UpdateCuttingFunction(void)
{
    if(nullptr != laserTrajModePtr)
    {
        laserTrajModePtr->UpdateData();
    }

}
void laser_cutting_module::ReadDxfFile(char *imfile)
{
    std::cout << "Reading file " << imfile << "...\n";

    DL_Dxf *laserCuttingDxf = new DL_Dxf();
    if (!laserCuttingDxf->in(imfile, &entityGraph))
    {
        // if file open failed
        std::cerr << imfile << " could not be opened.\n";
        return;
    }
    delete laserCuttingDxf;

}
void laser_cutting_module::WriteDxfFile(void)
{
    qDebug()<<"[HMI](laser_cutting_module)--Test write dxf file!";
    DL_Dxf* dxf = new DL_Dxf();
    DL_Codes::version exportVersion = DL_Codes::AC1015;
    DL_WriterA* dw = dxf->out("stronglasertest.dxf", exportVersion);
    if (dw == NULL)
    {
        qDebug()<<"[HMI](Laser cutting module)--Cannot open file 'cutting.dxf' for writing.!";
    }

    dxf->writeHeader(*dw);
    /*
    // int variable:
    dw->dxfString(9, "$INSUNITS");
    dw->dxfInt(70, 4);
    // real (double, float) variable:
    dw->dxfString(9, "$DIMEXE");
    dw->dxfReal(40, 1.25);
    // string variable:
    dw->dxfString(9, "$TEXTSTYLE");
    dw->dxfString(7, "Standard");
    // vector variable:
    dw->dxfString(9, "$LIMMIN");
    dw->dxfReal(10, 0.0);
    dw->dxfReal(20, 0.0);
    */
    dw->sectionEnd();
    dw->sectionTables();
    dxf->writeVPort(*dw);

    dw->tableLinetypes(3);
    dxf->writeLinetype(*dw, DL_LinetypeData("BYBLOCK", "BYBLOCK", 0, 0, 0.0));
    dxf->writeLinetype(*dw, DL_LinetypeData("BYLAYER", "BYLAYER", 0, 0, 0.0));
    dxf->writeLinetype(*dw, DL_LinetypeData("CONTINUOUS", "Continuous", 0, 0, 0.0));
    dw->tableEnd();

    int numberOfLayers = 3;
    dw->tableLayers(numberOfLayers);

    dxf->writeLayer(*dw,
                   DL_LayerData("0", 0),
                   DL_Attributes(
                       std::string(""),      // leave empty
                       DL_Codes::black,        // default color
                       100,                  // default width
                       "CONTINUOUS", 1.0));       // default line style

    dxf->writeLayer(*dw,
                   DL_LayerData("mainlayer", 0),
                   DL_Attributes(
                       std::string(""),
                       DL_Codes::red,
                       100,
                       "CONTINUOUS", 1.0));

    dxf->writeLayer(*dw,
                   DL_LayerData("anotherlayer", 0),
                   DL_Attributes(
                       std::string(""),
                       DL_Codes::black,
                       100,
                       "CONTINUOUS", 1.0));

    dw->tableEnd();

    dw->tableStyle(1);
    dxf->writeStyle(*dw, DL_StyleData("standard", 0, 2.5, 1.0, 0.0, 0, 2.5, "txt", ""));
    dw->tableEnd();

    dxf->writeView(*dw);
    dxf->writeUcs(*dw);

    dw->tableAppid(1);
    dxf->writeAppid(*dw, "ACAD");
    dw->tableEnd();

    dxf->writeDimStyle(*dw, 1, 1, 1, 1, 1);

    dxf->writeBlockRecord(*dw);
    dxf->writeBlockRecord(*dw, "myblock1");
    dxf->writeBlockRecord(*dw, "myblock2");
    dw->tableEnd();

    dw->sectionEnd();

    dw->sectionBlocks();
    dxf->writeBlock(*dw, DL_BlockData("*Model_Space", 0, 0.0, 0.0, 0.0));
    dxf->writeEndBlock(*dw, "*Model_Space");
    dxf->writeBlock(*dw, DL_BlockData("*Paper_Space", 0, 0.0, 0.0, 0.0));
    dxf->writeEndBlock(*dw, "*Paper_Space");
    dxf->writeBlock(*dw, DL_BlockData("*Paper_Space0", 0, 0.0, 0.0, 0.0));
    dxf->writeEndBlock(*dw, "*Paper_Space0");

    dxf->writeBlock(*dw, DL_BlockData("myblock1", 0, 0.0, 0.0, 0.0));
    // ...
    // write block entities e.g. with dxf->writeLine(), ..
    // ...
    dxf->writeEndBlock(*dw, "myblock1");

    dxf->writeBlock(*dw, DL_BlockData("myblock2", 0, 0.0, 0.0, 0.0));
    // ...
    // write block entities e.g. with dxf->writeLine(), ..
    // ...
    dxf->writeEndBlock(*dw, "myblock2");

    dw->sectionEnd();
    dw->sectionEntities();

    // write all entities in model space:
    dxf->writePoint(
        *dw,
        DL_PointData(10.0,
                     45.0,
                     0.0),
        DL_Attributes("mainlayer", 256, -1, "BYLAYER", 1.0));

    dxf->writeLine(
        *dw,
        DL_LineData(25.0,   // start point
                    30.0,
                    0.0,
                    100.0,   // end point
                    120.0,
                    0.0),
        DL_Attributes("mainlayer", 256, -1, "BYLAYER", 1.0));

    dw->sectionEnd();

    dxf->writeObjects(*dw);
    dxf->writeObjectsEnd(*dw);

    dw->dxfEOF();
    dw->close();
    delete dw;
    delete dxf;

}
void laser_cutting_module::SlotBtnFunction(QAbstractButton* funcBtn)
{
    qDebug() << QString("Clicked Button : %1").arg(funcBtn->text());
    if(!funcBtn->text().compare("加工模式"))
    {
        curFuncFlag = CUTTING_MODE;
        qDebug() << QString("Current select mode : %1").arg(funcBtn->text());
        WriteDxfFile();
    }
    else if(!funcBtn->text().compare("抓靶设定"))
    {
        curFuncFlag = VISION_MARKING_MODE;
        qDebug() << QString("Current select mode : %1").arg(funcBtn->text());
    }
    else if(!funcBtn->text().compare("机台设定"))
    {
        curFuncFlag = MACHIN_SET_MODE;
        qDebug() << QString("Current select mode : %1").arg(funcBtn->text());
    }
    else if(!funcBtn->text().compare("偏位校正"))
    {
        curFuncFlag = OFFSET_ADJUST;
        qDebug() << QString("Current select mode : %1").arg(funcBtn->text());
    }
    else if(!funcBtn->text().compare("振镜校正"))
    {
        curFuncFlag = GALVO_ADJUST;
        qDebug() << QString("Current select mode : %1").arg(funcBtn->text());
    }
    else if(!funcBtn->text().compare("相机校正"))
    {
        curFuncFlag = CAMERA_ADJUST;
        qDebug() << QString("Current select mode : %1").arg(funcBtn->text());
    }
    else
    {
        // nothing to do
        qDebug() << QString("Current select mode : %1").arg("Error, not any function button!" + funcBtn->text());
    }

    // 遍历按钮，获取选中状态

    QList<QAbstractButton*> list = funcBtnGrp->buttons();
    foreach (QAbstractButton *pButton, list)
    {
        QString strStatus = pButton->isChecked() ? "Checked" : "Unchecked";
        //qDebug() << QString("Button : %1 is %2").arg(funcBtn->text()).arg(strStatus);
    }

}
// dxf format file function blew
//line
int laser_cutting_module::getLineLength(void)
{
    return entityGraph.lines.count();
}
double laser_cutting_module::getLinex1(int index)
{
    return entityGraph.lines.at(index).x1;
}
double laser_cutting_module::getLinex2(int index)
{
    return entityGraph.lines.at(index).x2;
}
double laser_cutting_module::getLiney1(int index)
{
    return entityGraph.lines.at(index).y1;
}
double laser_cutting_module::getLiney2(int index)
{
    return entityGraph.lines.at(index).y2;
}
//circle
int laser_cutting_module::getCircleLength(void)
{
    return entityGraph.circles.count();
}
double laser_cutting_module::getCirclex(int index)
{
    return entityGraph.circles.at(index).cx;
}
double laser_cutting_module::getCircley(int index)
{
    return entityGraph.circles.at(index).cy;
}
double laser_cutting_module::getCircleRadius(int index)
{
    return entityGraph.circles.at(index).radius;
}

//mtext
int laser_cutting_module::getMTextLength(void)
{
    return entityGraph.mtexts.count();
}
double laser_cutting_module::getMTextx(int index)
{
    return entityGraph.mtexts.at(index).ipx;
}
double laser_cutting_module::getMTexty(int index)
{
    return entityGraph.mtexts.at(index).ipy;
}
QString laser_cutting_module::getMTextStr(int index)
{
    return QString::fromStdString(entityGraph.mtexts.at(index).text);
}
double laser_cutting_module::getMTextSize(int index)
{
    return entityGraph.mtexts.at(index).height*3/4;
}

//ploy line
int laser_cutting_module::getPolyLineLength(void)
{
    return entityGraph.polylines.count();
}
double laser_cutting_module::getVertex1x(int index)
{
    return entityGraph.vertices.at(index*4).x;
}
double laser_cutting_module::getVertex2x(int index)
{
    return entityGraph.vertices.at(index*4+1).x;
}
double laser_cutting_module::getVertex3x(int index)
{
    return entityGraph.vertices.at(index*4+2).x;
}
double laser_cutting_module::getVertex4x(int index)
{
    return entityGraph.vertices.at(index*4+3).x;
}
double laser_cutting_module::getVertex1y(int index)
{
    return entityGraph.vertices.at(index*4).y;
}
double laser_cutting_module::getVertex2y(int index)
{
    return entityGraph.vertices.at(index*4+1).y;
}
double laser_cutting_module::getVertex3y(int index)
{
    return entityGraph.vertices.at(index*4+2).y;
}
double laser_cutting_module::getVertex4y(int index)
{
    return entityGraph.vertices.at(index*4+3).y;
}

//hatch edge and hatch color
int laser_cutting_module::getHatchLength(void)
{
    return entityGraph.hatchedges.count();
}
double laser_cutting_module::getHatchx(int index)
{
    return entityGraph.hatchedges.at(index).cx;
}
double laser_cutting_module::getHatchy(int index)
{
    return entityGraph.hatchedges.at(index).cy;
}
QString laser_cutting_module::getHatchColor(int index)
{
    return entityGraph.hatchcolors.at(index);
}
double laser_cutting_module::getHatchRadius(int index)
{
    return entityGraph.hatchedges.at(index).radius;
}
/*************************************************************************************
 *
 *读写xml文件
 *
**************************************************************************************/
//写xml
void laser_cutting_module::WriteXml(const QString &xmlfile)
{
    //打开或创建文件
        QFile file(xmlfile); //相对路径、绝对路径、资源路径都可以
        if(!file.open(QFile::WriteOnly|QFile::Truncate)) //可以用QIODevice，Truncate表示清空原来的内容
            return;

        QDomDocument doc;
        //写入xml头部
        QDomProcessingInstruction instruction; //添加处理命令
        instruction=doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");
        doc.appendChild(instruction);
        //添加根节点
        QDomElement root=doc.createElement("LXDDocument");
        doc.appendChild(root);
        //添加第一个子节点及其子元素
        QDomElement DocHeader=doc.createElement("DocHeader");
        DocHeader.setAttribute("DefaultChannel",1); //创建属性  其中键值对的值可以是各种类型
        DocHeader.setAttribute("HandleSeed",1009); //创建属性  其中键值对的值可以是各种类型
        QDomAttr ID=doc.createAttribute("ID"); //创建属性 值必须是字符串
        ID.setValue("{B037502B-232A-4C09-881F-61DC815C9F9E}");
        DocHeader.setAttributeNode(ID);
        QDomElement ExtMin=doc.createElement("ExtMin"); //创建子元素
        DocHeader.appendChild(ExtMin);
        QDomElement ExtMax=doc.createElement("ExtMax");
        ExtMax.setAttribute("X",100);
        ExtMax.setAttribute("Y",200);
        DocHeader.appendChild(ExtMax);
        QDomElement InsertBase=doc.createElement("InsertBase");
        DocHeader.appendChild(InsertBase);
        QDomElement HomeRef = doc.createElement("HomeRef");
        QDomAttr Enabled=doc.createAttribute("Enabled");
        Enabled.setValue("true");
        HomeRef.setAttributeNode(Enabled);
        HomeRef.setAttribute("RefType",3);
        DocHeader.appendChild(HomeRef);
        root.appendChild(DocHeader);

        QDomElement Technical = doc.createElement("Technical");
        QDomElement Channels = doc.createElement("Channels");

        for(int i = 0; i <MAX_LASER_GRP_NUM; i++)
        {
            QDomElement Channel = doc.createElement("Channel");
            Channel.setAttribute("channelPort",i);
            Channel.setAttribute("power",laserGrp[i].power);
            Channel.setAttribute("frequency",laserGrp[i].freq);
            Channel.setAttribute("duty",laserGrp[i].duty);
            Channels.appendChild(Channel);
        }

        Technical.appendChild(Channels);
        root.appendChild(Technical);

        QDomElement Entities = doc.createElement("Entities");
        Entities.setAttribute("handle",1);


        qDebug()<<"The graph max number = "<<entityGraph.topDataVectorPtr.length();
        for(int i = 0; i < entityGraph.topDataVectorPtr.length(); i++)
        {
            switch (entityGraph.topDataVectorPtr[i].type) {
            case POINT_TYPE:
                {
                    QDomElement point = doc.createElement("point");
                    point.setAttribute("handle",1001);
                    point.setAttribute("ChannelPort",1);
                    QDomElement location = doc.createElement("location");
                    location.setAttribute("X",((DL_PointData*)(entityGraph.topDataVectorPtr[i].cmPtr))->x);
                    location.setAttribute("Y",((DL_PointData*)(entityGraph.topDataVectorPtr[i].cmPtr))->y);
                    point.appendChild(location);
                    Entities.appendChild(point);
                }
                break;
            case LINE_TYPE:
                {
                    QDomElement line = doc.createElement("line");
                    line.setAttribute("handle",1001);
                    line.setAttribute("ChannelPort",1);
                    QDomElement point = doc.createElement("Point");
                    point.setAttribute("X",((DL_LineData*)(entityGraph.topDataVectorPtr[i].cmPtr))->x1);
                    point.setAttribute("Y",((DL_LineData*)(entityGraph.topDataVectorPtr[i].cmPtr))->y1);
                    line.appendChild(point);
                    point.setAttribute("X",((DL_LineData*)(entityGraph.topDataVectorPtr[i].cmPtr))->x2);
                    point.setAttribute("Y",((DL_LineData*)(entityGraph.topDataVectorPtr[i].cmPtr))->y2);
                    line.appendChild(point);
                    Entities.appendChild(line);
                }
                break;
            case ARC_TYPE:
                {
                    QDomElement arc = doc.createElement("Arc");
                    arc.setAttribute("handle",1001);
                    arc.setAttribute("ChannelPort",1);
                    QDomElement p0 = doc.createElement("P0");
                    p0.setAttribute("Cx",((DL_ArcData*)(entityGraph.topDataVectorPtr[i].cmPtr))->cx);
                    p0.setAttribute("Cy",((DL_ArcData*)(entityGraph.topDataVectorPtr[i].cmPtr))->cy);
                    arc.appendChild(p0);
                    QDomElement p1 = doc.createElement("P1");
                    p1.setAttribute("radius",((DL_ArcData*)(entityGraph.topDataVectorPtr[i].cmPtr))->radius);
                    arc.appendChild(p1);
                    QDomElement p2 = doc.createElement("P2");
                    p2.setAttribute("Angle1",((DL_ArcData*)(entityGraph.topDataVectorPtr[i].cmPtr))->angle1);
                    p2.setAttribute("Angle2",((DL_ArcData*)(entityGraph.topDataVectorPtr[i].cmPtr))->angle2);
                    arc.appendChild(p2);
                    Entities.appendChild(arc);
                }
                break;
            case CIRCLE_TYPE:
                {
                    QDomElement circle = doc.createElement("Circle");
                    circle.setAttribute("handle",1001);
                    circle.setAttribute("ChannelPort",1);
                    QDomElement p1 = doc.createElement("P1");
                    p1.setAttribute("Cx",((DL_CircleData*)(entityGraph.topDataVectorPtr[i].cmPtr))->cx);
                    p1.setAttribute("Cy",((DL_CircleData*)(entityGraph.topDataVectorPtr[i].cmPtr))->cy);
                    circle.appendChild(p1);
                    QDomElement p2 = doc.createElement("P2");
                    p2.setAttribute("Radius",((DL_CircleData*)(entityGraph.topDataVectorPtr[i].cmPtr))->radius);
                    circle.appendChild(p2);
                    Entities.appendChild(circle);
                }
                break;
            case ELLIPSE_TYPE:
                {
                    QDomElement ellipse = doc.createElement("Ellipse");
                    ellipse.setAttribute("handle",1001);
                    ellipse.setAttribute("ChannelPort",1);
                    QDomElement p1 = doc.createElement("P1");
                    p1.setAttribute("Cx",((DL_EllipseData*)(entityGraph.topDataVectorPtr[i].cmPtr))->cx);
                    p1.setAttribute("Cy",((DL_EllipseData*)(entityGraph.topDataVectorPtr[i].cmPtr))->cy);
                    ellipse.appendChild(p1);
                    QDomElement p2 = doc.createElement("P2");
                    p2.setAttribute("Mx",((DL_EllipseData*)(entityGraph.topDataVectorPtr[i].cmPtr))->mx);
                    p2.setAttribute("My",((DL_EllipseData*)(entityGraph.topDataVectorPtr[i].cmPtr))->my);
                    ellipse.appendChild(p2);
                    QDomElement p3 = doc.createElement("P3");
                    p3.setAttribute("Ratio",((DL_EllipseData*)(entityGraph.topDataVectorPtr[i].cmPtr))->ratio);
                    ellipse.appendChild(p3);
                    QDomElement p4 = doc.createElement("P4");
                    p4.setAttribute("Angle1",((DL_EllipseData*)(entityGraph.topDataVectorPtr[i].cmPtr))->angle1);
                    p4.setAttribute("Angle2",((DL_EllipseData*)(entityGraph.topDataVectorPtr[i].cmPtr))->angle2);
                    ellipse.appendChild(p4);
                    Entities.appendChild(ellipse);
                }
                break;
            case TEXT_TYPE:
                break;
            case DIMANGULAR_TYPE:
                break;
            case DIMLINEAR_TYPE:
                break;
            case VERTEX_TYPE:
                {
                    QDomElement polyline = doc.createElement("Polyline");
                    polyline.setAttribute("handle",1001);
                    polyline.setAttribute("ChannelPort",1);
                    QDomElement point = doc.createElement("Point");
                    point.setAttribute("X",((DL_VertexData*)(entityGraph.topDataVectorPtr[i].cmPtr))->x);
                    point.setAttribute("Y",((DL_VertexData*)(entityGraph.topDataVectorPtr[i].cmPtr))->y);
                    polyline.appendChild(point);
                    point.setAttribute("X",((DL_VertexData*)(entityGraph.topDataVectorPtr[i].cmPtr))->x);
                    point.setAttribute("Y",((DL_VertexData*)(entityGraph.topDataVectorPtr[i].cmPtr))->y);
                    polyline.appendChild(point);
                    Entities.appendChild(polyline);
                }
                break;
            case POLYLINE_TYPE:
                qDebug()<<QString("----------------------->>>>>The graph type =POLYLINE_TYPE");
                break;
            case MTEXT_TYPE:
                {
                    QDomElement mtest = doc.createElement("Mtest");
                    mtest.setAttribute("handle",1001);
                    mtest.setAttribute("ChannelPort",1);
                    QDomElement p1 = doc.createElement("P1");
                    p1.setAttribute("Ipx",((DL_MTextData*)(entityGraph.topDataVectorPtr[i].cmPtr))->ipx);
                    p1.setAttribute("Ipy",((DL_MTextData*)(entityGraph.topDataVectorPtr[i].cmPtr))->ipy);
                    mtest.appendChild(p1);
                    QDomElement p2 = doc.createElement("P2");
                    p2.setAttribute("Dirx",((DL_MTextData*)(entityGraph.topDataVectorPtr[i].cmPtr))->dirx);
                    p2.setAttribute("Dirx",((DL_MTextData*)(entityGraph.topDataVectorPtr[i].cmPtr))->diry);
                    mtest.appendChild(p2);
                    QDomElement p3 = doc.createElement("P3");
                    p3.setAttribute("Factor",((DL_MTextData*)(entityGraph.topDataVectorPtr[i].cmPtr))->lineSpacingFactor);
                    mtest.appendChild(p3);
                    QDomElement p4 = doc.createElement("P4");
                    QDomAttr instring=doc.createAttribute("Text");
                    instring.setValue(QString::fromStdString(((DL_MTextData*)(entityGraph.topDataVectorPtr[i].cmPtr))->text));
                    p4.setAttributeNode(instring);
                    mtest.appendChild(p4);
                    Entities.appendChild(mtest);
                }
                break;
            case HATCH_TYPE:
                break;
            case HATCH_EDGE_TYPE:
                break;
            case QSTRING_HATCHCOLOR_TYPE:
                break;
            default:
                qDebug() << QString("unkown type");
                break;
            }
        }


        root.appendChild(Entities);
        doc.appendChild(root);


        //输出到文件
        QTextStream out_stream(&file);
        doc.save(out_stream,4); //缩进4格
        file.close();

}

//读xml
void laser_cutting_module::ReadXml(const QString &rfile)
{
    //打开或创建文件
    QFile file(rfile); //相对路径、绝对路径、资源路径都行
    if(!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root=doc.documentElement(); //返回根节点
    qDebug()<<root.nodeName();
    QDomNode node=root.firstChild(); //获得第一个子节点
    while(!node.isNull())  //如果节点不空
    {
        if(node.isElement()) //如果节点是元素
        {
            QDomElement e=node.toElement(); //转换为元素，注意元素和节点是两个数据结构，其实差不多
            qDebug()<<e.tagName()<<" "<<e.attribute("id")<<" "<<e.attribute("time"); //打印键值对，tagName和nodeName是一个东西
            QDomNodeList list=e.childNodes();
            for(int i=0;i<list.count();i++) //遍历子元素，count和size都可以用,可用于标签数计数
            {
                QDomNode n=list.at(i);
                if(node.isElement())
                    qDebug()<<n.nodeName()<<":"<<n.toElement().text();
            }
        }
        node=node.nextSibling(); //下一个兄弟节点,nextSiblingElement()是下一个兄弟元素，都差不多
    }

}

//增加xml内容
void laser_cutting_module::AddXml(const QString &xmlfile)
{
    //打开文件
    QFile file(xmlfile); //相对路径、绝对路径、资源路径都可以
    if(!file.open(QFile::ReadOnly))
        return;

    //增加一个一级子节点以及元素
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root=doc.documentElement();
    QDomElement book=doc.createElement("book");
    book.setAttribute("id",3);
    book.setAttribute("time","1813/1/27");
    QDomElement title=doc.createElement("title");
    QDomText text;
    text=doc.createTextNode("Pride and Prejudice");
    title.appendChild(text);
    book.appendChild(title);
    QDomElement author=doc.createElement("author");
    text=doc.createTextNode("Jane Austen");
    author.appendChild(text);
    book.appendChild(author);
    root.appendChild(book);

    if(!file.open(QFile::WriteOnly|QFile::Truncate)) //先读进来，再重写，如果不用truncate就是在后面追加内容，就无效了
        return;
    //输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();
}

//删减xml内容
void laser_cutting_module::RemoveXml(const QString &xmlfile)
{
    //打开文件
    QFile file(xmlfile); //相对路径、绝对路径、资源路径都可以
    if(!file.open(QFile::ReadOnly))
        return;

    //删除一个一级子节点及其元素，外层节点删除内层节点于此相同
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();  //一定要记得关掉啊，不然无法完成操作

    QDomElement root=doc.documentElement();
    QDomNodeList list=doc.elementsByTagName("book"); //由标签名定位
    for(int i=0;i<list.count();i++)
    {
        QDomElement e=list.at(i).toElement();
        if(e.attribute("time")=="2007/5/25")  //以属性名定位，类似于hash的方式，warning：这里仅仅删除一个节点，其实可以加个break
            root.removeChild(list.at(i));
    }

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    //输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();
}

//更新xml内容
void laser_cutting_module::UpdateXml(const QString &xmlfile)
{
    //打开文件
    QFile file(xmlfile); //相对路径、绝对路径、资源路径都可以
    if(!file.open(QFile::ReadOnly))
        return;

    //更新一个标签项,如果知道xml的结构，直接定位到那个标签上定点更新
    //或者用遍历的方法去匹配tagname或者attribut，value来更新
    QDomDocument doc;
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement root=doc.documentElement();
    QDomNodeList list=root.elementsByTagName("book");
    QDomNode node=list.at(list.size()-1).firstChild(); //定位到第三个一级子节点的子元素
    QDomNode oldnode=node.firstChild(); //标签之间的内容作为节点的子节点出现,当前是Pride and Projudice
    node.firstChild().setNodeValue("Emma");
    QDomNode newnode=node.firstChild();
    node.replaceChild(newnode,oldnode);

    if(!file.open(QFile::WriteOnly|QFile::Truncate))
        return;
    //输出到文件
    QTextStream out_stream(&file);
    doc.save(out_stream,4); //缩进4格
    file.close();
}
// 工艺操作缓存队列
void laser_cutting_module::TechList(void)
{

}
