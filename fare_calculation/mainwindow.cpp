#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_released() //1ヶ月定期
{
    //利用終了日に<利用開始日>と<期間に応じて>日付をセット
    //定期券の利用終了日は1ヶ月定期のみ利用開始日の1日前
    //利用終了日が2月の存在しない日付の場合(30日など)は、2月の最終日が利用終了日となる

    ui->label_month->setText("1");//｢nヶ月の料金｣のnに1を代入
    if(ui->month1->value()==1 && ui->day1->value()>29 && ui->year1->value()%4==0 && (ui->year1->value()%100!=0 || ui->year1->value()%400!=0)){
        ui->day2->setValue(29);
    }//うるう年の2月の場合、
    else if(ui->month1->value()==1 && ui->day1->value()>29 && (ui->year1->value()%4!=0 || ui->year1->value()%100==0) ){
        ui->day2->setValue(28);
    }//うるう年ではない2月
    else{
        ui->day2->setValue(ui->day1->value()-1);
    }//それ以外の月
    //年をまたがない場合
    if(ui->month1->value()<12){
        ui->year2->setValue(ui->year1->value() );
        ui->month2->setValue(ui->month1->value()+1);
    }
    //年をまたぐ場合
    else{
        ui->year2->setValue(ui->year1->value()+1);
        ui->month2->setValue((ui->month1->value()+1)%12);
    }
}
//以上の手順を他の期間でも繰り返す
void MainWindow::on_pushButton_3_released() //3ヶ月定期
{
    ui->label_month->setText("3");//｢nヶ月の料金｣のnに3を代入
    ui->day2->setValue(ui->day1->value());
    if(ui->month1->value()<10){
        ui->year2->setValue(ui->year1->value() );
        ui->month2->setValue(ui->month1->value()+3);
    }
    else{
        ui->year2->setValue(ui->year1->value()+1);
        ui->month2->setValue((ui->month1->value()+3)%12);
    }
}

void MainWindow::on_pushButton_6_released() //6ヶ月定期
{
    ui->label_month->setText("6");//｢nヶ月の料金｣のnに6を代入
    ui->day2->setValue(ui->day1->value());
    if(ui->month1->value()<7){
        ui->year2->setValue(ui->year1->value() );
        ui->month2->setValue(ui->month1->value()+6);
    }
    else{
        ui->year2->setValue(ui->year1->value()+1);
        ui->month2->setValue((ui->month1->value()+6)%12);
    }
}

void MainWindow::on_pushButton_12_released() //1年定期
{
    ui->label_month->setText("12");//｢nヶ月の料金｣のnに12を代入
    ui->day2->setValue(ui->day1->value());
    ui->month2->setValue(ui->month1->value());
    ui->year2->setValue(ui->year1->value()+1);
}



void MainWindow::on_pushButton_Restday_released() //利用しない日数計算
//経過日数を近似的な一次関数として計算
//参考：https://ufcpp.net/study/algorithm/o_days.html
{int dy2; int dy1; int c2; int c1; int dl2; int dl1; int dm2; int dm1;
//1月2月は前年の13月14月として計算するので、1月2月を含むかどうかで場合分けをして計算する
    if (ui->month2_2->value() <= 2 && ui->month1_2->value() <= 2)
            {
              dy2 = 365 * (((ui->year2_2->value()+2000)-1) - 1);
              c2 = ((ui->year2_2->value()+2000)-1 )/ 100;
              dl2 = (((ui->year2_2->value()+2000)-1) /4) - c2 + (c2 /4);
              dm2 = ((ui->month2_2->value()+12) * 979 - 1033) /32;
              dy1 = 365 * (((ui->year1_2->value()+2000)-1) - 1);
              c1 = ((ui->year1_2->value()+2000)-1) / 100;
              dl1 = (((ui->year1_2->value()+2000)-1) /4) - c1 + (c1 /4);
              dm1 = ((ui->month1_2->value()+12) * 979 - 1033) /32;
            }
            else if (ui->month2_2->value() <= 2 && ui->month1_2->value() > 2)
            {
              dy2 = 365 * (((ui->year2_2->value()+2000)-1)  - 1);
              c2 = ((ui->year2_2->value()+2000)-1)  / 100;
              dl2 = (((ui->year2_2->value()+2000)-1)  /4) - c2 + (c2 /4);
              dm2 = ((ui->month2_2->value()+12) * 979 - 1033) /32;
              dy1 = 365 * ((ui->year1_2->value()+2000) - 1);
              c1 = (ui->year1_2->value()+2000) / 100;
              dl1 = ((ui->year1_2->value()+2000) /4) - c1 + (c1 /4);
              dm1 = (ui->month1_2->value() * 979 - 1033) /32;
            }
            else if(ui->month2_2->value() > 2 && ui->month1_2->value() <= 2)
            {
              dy2 = 365 * ((ui->year2_2->value()+2000) - 1);
              c2 = (ui->year2_2->value()+2000) / 100;
              dl2 = ((ui->year2_2->value()+2000) /4) - c2 + (c2 /4);
              dm2 = (ui->month2_2->value() * 979 - 1033) /32;
              dy1 = 365 * (((ui->year1_2->value()+2000)-1)  - 1);
              c1 = ((ui->year1_2->value()+2000)-1)  / 100;
              dl1 = (((ui->year1_2->value()+2000)-1)  /4) - c1 + (c1 /4);
              dm1 = ((ui->month1_2->value()+12) * 979 - 1033)/32;
            }
            else{
              dy2 = 365 * ((ui->year2_2->value()+2000) - 1);
              c2 = (ui->year2_2->value()+2000) / 100;
              dl2 = ((ui->year2_2->value()+2000) /4) - c2 + (c2 /4);
              dm2 = (ui->month2_2->value() * 979 - 1033) /32;
              dy1 = 365 * ((ui->year1_2->value()+2000) - 1);
              c1 = (ui->year1_2->value()+2000) / 100;
              dl1 = ((ui->year1_2->value()+2000) /4) - c1 + (c1 /4);
              dm1 = (ui->month1_2->value() * 979 - 1033) /32;
        }

    if( ui->year2_2->value()-ui->year1_2->value()>1)
      {
        ui->label_error1->setText("error");
      }
      else{
        ui->daysStop->setValue((dy2 + dl2 + dm2 + ui->day2_2->value()) - (dy1 + dl1 + dm1 + ui->day1_2->value()));
        }

}

void MainWindow::on_Button_Result_released()  //利用日数計算
//経過日数を近似的な一次関数として計算
//参考：https://ufcpp.net/study/algorithm/o_days.html
{int Dy2; int Dy1; int C2; int C1; int Dl2; int Dl1; int Dm2; int Dm1;
//1月2月は前年の13月14月として計算するので、1月2月を含むかどうかで場合分けをして計算する
    if (ui->month2->value() <= 2 && ui->month1->value() <= 2)
                {
                  Dy2 = 365 * (((ui->year2->value()+2000)-1) - 1);
                  C2 = ((ui->year2->value()+2000)-1 )/ 100;
                  Dl2 = (((ui->year2->value()+2000)-1) /4) - C2 + (C2 /4);
                  Dm2 = ((ui->month2->value()+12) * 979 - 1033) /32;
                  Dy1 = 365 * (((ui->year1->value()+2000)-1) - 1);
                  C1 = ((ui->year1->value()+2000)-1) / 100;
                  Dl1 = (((ui->year1->value()+2000)-1) /4) - C1 + (C1 /4);
                  Dm1 = ((ui->month1->value()+12) * 979 - 1033) /32;
                }
    else if (ui->month2->value() <= 2 && ui->month1->value() > 2)
                {
                  Dy2 = 365 * (((ui->year2->value()+2000)-1)  - 1);
                  C2 = ((ui->year2->value()+2000)-1)  / 100;
                  Dl2 = (((ui->year2->value()+2000)-1)  /4) - C2 + (C2 /4);
                  Dm2 = ((ui->month2->value()+12) * 979 - 1033) /32;
                  Dy1 = 365 * ((ui->year1->value()+2000) - 1);
                  C1 = (ui->year1->value()+2000) / 100;
                  Dl1 = ((ui->year1->value()+2000) /4) - C1 + (C1 /4);
                  Dm1 = (ui->month1->value() * 979 - 1033) /32;
                }
    else if(ui->month2->value() > 2 && ui->month1->value() <= 2)
                {
                  Dy2 = 365 * ((ui->year2->value()+2000) - 1);
                  C2 = (ui->year2->value()+2000) / 100;
                  Dl2 = ((ui->year2->value()+2000) /4) - C2 + (C2 /4);
                  Dm2 = (ui->month2->value() * 979 - 1033) /32;
                  Dy1 = 365 * (((ui->year1->value()+2000)-1)  - 1);
                  C1 = ((ui->year1->value()+2000)-1)  / 100;
                  Dl1 = (((ui->year1->value()+2000)-1)  /4) - C1 + (C1 /4);
                  Dm1 = ((ui->month1->value()+12) * 979 - 1033) /32;
                }
    else{
                  Dy2 = 365 * ((ui->year2->value()+2000) - 1);
                  C2 = (ui->year2->value()+2000) / 100;
                  Dl2 = ((ui->year2->value()+2000) /4) - C2 + (C2 /4);
                  Dm2 = (ui->month2->value() * 979 - 1033) /32;
                  Dy1 = 365 * ((ui->year1->value()+2000) - 1);
                  C1 = (ui->year1->value()+2000) / 100;
                  Dl1 = ((ui->year1->value()+2000) /4) - C1 + (C1 /4);
                  Dm1 = (ui->month1->value() * 979 - 1033) /32;
            }

//結果反映
    //1年以内のみ結果を反映
    if( ui->year2->value()-ui->year1->value()>1)
    {ui->label_error2->setText("2年以上の計算は対応していません");}
    else{
        ui->daysResult->setValue(((Dy2 + Dl2 + Dm2 + ui->day2->value()) - (Dy1 + Dl1 + Dm1 + ui->day1->value()))-ui->daysStop->value());
    }
}

void MainWindow::on_pushButton_finalresult_released() //定期券判定
{//fare=定期運賃 fare1=通常片道運賃
    //何も入力されていない場合
    if(ui->fare->value()==0 || ui->fare1->value()==0 || ui->daysResult->value()==0){
        ui->label_finalresult2->setText("日数･料金などを入力してください");
    }
    //定期券を買ったほうが得な場合(差がない場合も含む)
    else if(ui->fare->value()-(ui->fare1->value()*2*ui->daysResult->value())<=0){
        ui->label_finalresult1->setText("定期券を買ったほうが");
        ui->label_finalresult2->setNum(-(ui->fare->value()-(ui->fare1->value()*2*ui->daysResult->value())));
        ui->label_finalresult3->setText("円お得です");
    }
    //定期券を買うと損する場合
    else if(ui->fare->value()-(ui->fare1->value()*ui->daysResult->value()*2)>0){
        ui->label_finalresult1->setText("定期券を買うと");
        ui->label_finalresult2->setNum(ui->fare->value()-(ui->fare1->value()*2*ui->daysResult->value()));
        ui->label_finalresult3->setText("円損です");
        }
}



