#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include "TF1.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TLegend.h"
#include "TStyle.h"

#define N 6
#define out_name "fit_congiunto.pdf"
#define in_name "dati_%d.txt"

void fit() 
{
    gStyle->SetOptFit(1111);
    TCanvas *c_1 = new TCanvas("c_1", "fit exp", 800, 600);
    TCanvas *c_2 = new TCanvas("c_2", "fit tanh", 800, 600);
    TMultiGraph *mg_1 = new TMultiGraph();
    TMultiGraph *mg_2 = new TMultiGraph();
    //TLegend *leg = new TLegend(0, 0.2, 0.4, 0.6, 0.8, 1.5);
    string dummy;
    Int_t i,j,n;
    Double_t V[100], I[100], V_err[100], I_err[100];
    
    for(i=0; i<N; i++)
        {
            fstream in(Form(in_name, i), ios::in);
            if (in.is_open())
                {  
                    getline(in,dummy);
                    in>>n;
                    for(j=0; j<n; j++)
                        {
                            in>>V[j]>>V_err[j]>>I[j]>>I_err[j];
                        }
                    TGraphErrors *g_1 = new TGraphErrors(n, V, I, V_err, I_err);
                    TF1 *f_1 = new TF1(Form("f_exp_%d", i), "[0]*(1-exp([1]*x))", 0, 100); 
                    f_1->SetParameters(10, 0.1);
                    g_1->Fit(f_1, "Q");
                    g_1->SetMarkerStyle(20 + i);
                    g_1->SetMarkerColor(i + 2);
                    g_1->SetLineColor(i + 2);
                    mg_1->Add(g_1, "P");

                    TGraphErrors *g_2 = new TGraphErrors(n, V, I, V_err, I_err);
                    TF1 *f_2 = new TF1(Form("f_tanh_%d", i), "[0]*tanh([1]*x)*([2]*x+1)", 0, 100);
                    f_2->SetParameters(2,0); 
                    g_2->Fit(f_2, "Q");
                    g_2->SetMarkerStyle(20 + i);
                    g_2->SetMarkerColor(i + 2);
                    g_2->SetLineColor(i + 2);
                    mg_2->Add(g_2, "P");
                }
        }
    c_1->cd();
    mg_1->Draw("A"); 
    mg_1->GetXaxis()->SetTitle("Tensione (V)");
    mg_1->GetYaxis()->SetTitle("Corrente (mA)");
    mg_1->SetTitle("Sovrapposizione Fit Caratteristici");

    c_2->cd();
    mg_2->Draw("A"); 
    mg_2->GetXaxis()->SetTitle("Tensione (V)");
    mg_2->GetYaxis()->SetTitle("Corrente (mA)");
    mg_2->SetTitle("Sovrapposizione Fit Caratteristici");
}