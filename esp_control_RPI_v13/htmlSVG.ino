#if defined usePID
//____________________________________________________________________________________show_tuningHTML
String show_tuningSVG() {                                                            // rev 1.3b use SVG
  String svg = ("");
  svg += ("<?xml version=\"1.0\" standalone=\"no\"?>");
  svg += ("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" ");
  svg += ("\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">");
  svg += ("<svg width=\"200\" height=\"260\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">");
  svg += ("<desc>make a face plate for tuning PID </desc>");
// inline CSS class w12 ( big left ) w10 (small left ) w12r ( big right x!)
  svg +=("<defs>");
  svg +=("  <style type=\"text/css\"><![CDATA[");
  svg +=("    text.w12 {");
  svg +=("      font-family: Verdana;");
  svg +=("      font-size: 12px;");
  svg +=("      fill: #ffffff;");
  svg +=("      text-anchor: start;");
  svg +=("    }");
  svg +=("    text.w10 {");
  svg +=("      font-family: Verdana;");
  svg +=("      font-size: 10px;");
  svg +=("      fill: #ffffff;");
  svg +=("      text-anchor: start;");
  svg +=("    }");
  svg +=("    text.w12r {");
  svg +=("      font-family: Verdana;");
  svg +=("      font-size: 12px;");
  svg +=("      fill: #ffffff;");
  svg +=("      text-anchor: end;");
  svg +=("    }");
  svg +=("  ]]></style>");
  svg +=("</defs>");
  
  svg += ("<!-- grey box with 3D style blue border-->");
  svg += ("<rect x=\"1\" y=\"1\" width=\"200\" height=\"260\"  stroke=\"#000088\" stroke-width=\"1\" />");
  svg += ("<rect x=\"2\" y=\"2\" width=\"196\" height=\"256\"  stroke=\"#0000aa\" stroke-width=\"1\" />");
  svg += ("<rect x=\"3\" y=\"3\" width=\"194\" height=\"254\"  fill=\"#dddddd\" stroke=\"#0000ff\" stroke-width=\"1\" />");
  svg += ("<g id=\"PID\" style=\"visibility:visible\"> ");

  svg += ("<rect x=\"10\"  y=\"10\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"23\" >tPI</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"23\" >tune P GAIN</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"23\" >"); svg += (PID1_gain); svg += ("</text>");

  svg += ("<rect x=\"10\"  y=\"30\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"43\" >tII</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"43\" >tune I RESET</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"43\" >"); svg += (PID1_reset); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"50\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"63\" >tDI</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"63\" >tune D RATE</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"63\" >"); svg += (PID1_rate); svg += ("</text>");
 
  svg += ("<rect x=\"10\"   y=\"70\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"83\" >tAI</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"83\" >tune action</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"83\" >"); svg += (PID1_action); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"90\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"103\" >tOI</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"103\" >tune rev out</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"103\" >"); svg += (PID1_outdir); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"110\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"123\" >tTI</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"123\" >cycle time</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"123\" >"); svg += (PID1_Ctimlim); svg += ("</text>");
  
  svg += ("</g>");   svg += ("</svg>\r\n");
  
return svg;  
}

String show_tuninganalogSVG() {                                                            // rev 1.3b use SVG
  String svg = ("");
  svg += ("<?xml version=\"1.0\" standalone=\"no\"?>");
  svg += ("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" ");
  svg += ("\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">");
  svg += ("<svg width=\"200\" height=\"260\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">");
  svg += ("<desc>make a face plate for tuning analog PID IND </desc>");
// inline CSS class w12 ( big left ) w10 (small left ) w12r ( big right x!)
  svg +=("<defs>");
  svg +=("  <style type=\"text/css\"><![CDATA[");
  svg +=("    text.w12 {");
  svg +=("      font-family: Verdana;");
  svg +=("      font-size: 12px;");
  svg +=("      fill: #ffffff;");
  svg +=("      text-anchor: start;");
  svg +=("    }");
  svg +=("    text.w10 {");
  svg +=("      font-family: Verdana;");
  svg +=("      font-size: 10px;");
  svg +=("      fill: #ffffff;");
  svg +=("      text-anchor: start;");
  svg +=("    }");
  svg +=("    text.w12r {");
  svg +=("      font-family: Verdana;");
  svg +=("      font-size: 12px;");
  svg +=("      fill: #ffffff;");
  svg +=("      text-anchor: end;");
  svg +=("    }");
  svg +=("  ]]></style>");
  svg +=("</defs>");
  
  svg += ("<!-- grey box with 3D style blue border-->");
  svg += ("<rect x=\"1\" y=\"1\" width=\"200\" height=\"260\"  stroke=\"#000088\" stroke-width=\"1\" />");
  svg += ("<rect x=\"2\" y=\"2\" width=\"196\" height=\"256\"  stroke=\"#0000aa\" stroke-width=\"1\" />");
  svg += ("<rect x=\"3\" y=\"3\" width=\"194\" height=\"254\"  fill=\"#dddddd\" stroke=\"#0000ff\" stroke-width=\"1\" />");
  svg += ("<g id=\"PIDa\" style=\"visibility:visible\"> ");

  svg += ("<rect x=\"10\"   y=\"10\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"23\" >EGU</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"23\" >engineering units</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"23\" >"); svg += (PID1_EGU); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"30\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"43\" >LOR</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"43\" >PV low range</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"43\" >"); svg += (PID1_LOR); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"50\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"63\" >HIR</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"63\" >PV high range</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"63\" >"); svg += (PID1_HIR); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"70\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"83\" >ALL</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"83\" >PV lo lo alarm</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"83\" >"); svg += (PID1_PVALL); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"90\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"103\" >ALO</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"103\" >PV lo alarm</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"103\" >"); svg += (PID1_PVALO); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"110\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"123\" >AHI</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"123\" >PV hi alarm</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"123\" >"); svg += (PID1_PVAHI); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"130\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"143\" >AHH</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"143\" >PV hi hi alarm</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"143\" >"); svg += (PID1_PVAHH); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"150\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"163\" >tPV</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"163\" >PV filter</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"163\" >"); svg += (PID1_PVfil0); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"170\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"183\" >LOV</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"183\" >output low alarm</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"183\" >"); svg += (PID1_OVALO); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"190\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"203\" >OLL</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"203\" >output low lim</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"203\" >"); svg += (PID1_outmin); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"210\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"223\" >HOV</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"223\" >output hi alarm</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"223\" >"); svg += (PID1_OVAHI); svg += ("</text>");

  svg += ("<rect x=\"10\"   y=\"230\" width=\"180\"  height=\"18\" fill=\"#777777\" />");
  svg += ("<text class=\"w12\" x=\"12\"  y=\"243\" >OLH</text>");
  svg += ("<text class=\"w10\" x=\"47\"  y=\"243\" >output hi lim</text>");
  svg += ("<text class=\"w12r\" x=\"185\" y=\"243\" >"); svg += (PID1_outmax); svg += ("</text>");
 
  
  svg += ("</g>");   svg += ("</svg>\r\n");
  
return svg;  
}



String show_PID_FP_SVG() {                                                            // rev 1.3b use SVG
  String svg = ("");
  svg += ("<?xml version=\"1.0\" standalone=\"no\"?>");
  svg += ("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" ");
  svg += ("\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">");
  svg += ("<svg width=\"200\" height=\"260\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">");
  svg += ("<desc>make a face plate for PID FP faceplate </desc>");
  svg += ("<!-- grey box with 3D style blue border-->");
  svg += ("<rect x=\"1\" y=\"1\" width=\"200\" height=\"260\"  stroke=\"#000088\" stroke-width=\"1\" />");
  svg += ("<rect x=\"2\" y=\"2\" width=\"196\" height=\"256\"  stroke=\"#0000aa\" stroke-width=\"1\" />");
  svg += ("<rect x=\"3\" y=\"3\" width=\"194\" height=\"254\"  fill=\"#dddddd\" stroke=\"#0000ff\" stroke-width=\"1\" />");
  svg += ("<g id=\"PID_FP\" style=\"visibility:visible\"> ");
  svg += ("<!-- point info -->");
  svg += ("<text x=\"100\" y=\"18\" font-family=\"Verdana\" font-size=\"15\" fill=\"black\" text-anchor=\"middle\">"); svg += (PID1_TAG); svg += ("</text>");
  svg += ("<text x=\"100\" y=\"32\" font-family=\"Verdana\" font-size=\"12\" fill=\"black\" text-anchor=\"middle\">"); svg += (PID1_DESC); svg += ("</text>");
  svg += ("<!-- Alarm text  ALM text background rectangle -->");

  svg += ("<text x=\"150\" y=\"217\" font-family=\"Verdana\" font-size=\"12\" fill=\"red\"  text-anchor=\"middle\">"); svg += (PID1_tALM[PID1_ALM]); svg += ("</text>");


//  svg += ("<!-- yellow PV value + EGU --> ");
  svg += ("<rect x=\"100\" y=\"61\" width=\"93\"  height=\"38\" fill=\"#777777\" />  <!-- PV text background rectangle -->");  // use PV in EGU
  svg += ("<text x=\"150\" y=\"76\" font-family=\"Verdana\" font-size=\"12\" fill=\"yellow\"  text-anchor=\"middle\">"); svg += (PID1_RPV); svg += ("</text>");
  svg += ("<text x=\"150\" y=\"91\" font-family=\"Verdana\" font-size=\"12\" fill=\"yellow\"  text-anchor=\"middle\">["); svg += (PID1_EGU); svg += ("]</text>");
//  svg += ("<!-- yellow PV bar--> ");
  svg += ("<rect x=\"35\" y=\"40\" width=\"20\" fill=\"#ffff00\" height=\"202\"/>");
  int bPV = 200 - int(2*PID1_PV);   // use PV in %
  svg += ("<rect x=\"36\" y=\"41\" width=\"18\" fill=\"#777777\" height=\""); svg += (bPV); svg += ("\"/>");

//  svg += ("<!-- range info -->");
  svg += ("<rect x=\"80\" y=\"40\" width=\"64\"  height=\"17\" fill=\"#777777\" />"); //  <!-- HIR text background rectangle -->
  svg += ("<text x=\"112\" y=\"53\" font-family=\"Verdana\" font-size=\"12\" fill=\"white\"  text-anchor=\"middle\">"); svg += (PID1_HIR); svg += ("</text>");
  svg += ("<rect x=\"80\" y=\"225\" width=\"64\"  height=\"17\" fill=\"#777777\" />"); //  <!-- LOR text background rectangle -->");
  svg += ("<text x=\"112\" y=\"238\" font-family=\"Verdana\" font-size=\"12\" fill=\"white\"  text-anchor=\"middle\">"); svg += (PID1_LOR); svg += ("</text>");
/*
  svg += ("<!-- alarm limits as red line -->");
{% if dbi.ALL > 0.0 %}
  svg += ("<line x1='32' y1='{{ 40 + 2 * (100 - dbi.ALL) }}' x2='58' y2='{{ 40 + 2 * (100 - dbi.ALL) }}' style=\"stroke:rgb(255,0,0);stroke-width:2\" />");
{% endif %}
{% if dbi.ALO > 0.0 %}
  svg += ("<line x1='32' y1='{{ 40 + 2 * (100 - dbi.ALO) }}' x2='58' y2='{{ 40 + 2 * (100 - dbi.ALO) }}' style=\"stroke:rgb(255,0,0);stroke-width:2\" />");
{% endif %}
{% if dbi.AHI < 100.0 %}
  svg += ("<line x1='32' y1='{{ 40 + 2 * (100 - dbi.AHI) }}' x2='58' y2='{{ 40 + 2 * (100 - dbi.AHI) }}' style=\"stroke:rgb(255,0,0);stroke-width:2\" />");
{% endif %}
{% if dbi.AHH < 100.0 %}
  svg += ("<line x1='32' y1='{{ 40 + 2 * (100 - dbi.AHH) }}' x2='58' y2='{{ 40 + 2 * (100 - dbi.AHH) }}' style=\"stroke:rgb(255,0,0);stroke-width:2\" />");
{% endif %} 
*/
  svg += ("<!-- cyan OUTPUT bar-->");
  svg += ("<rect x=\"10\" y=\"40\" width=\"20\" fill=\"#00ffff\" height=\"202\"/>");
  int bOV = 200 - int(2*PID1_OV);
  svg += ("<rect x=\"11\" y=\"41\" width=\"18\" fill=\"#777777\" height=\""); svg += (bOV); svg += ("\"/>");
/*
  svg += ("<!-- alarm limits as red line -->");
{% if dbi.LOV > 0.0 %}
  svg += ("<line x1='7' y1='{{ 40 + 2 * (100 - dbi.LOV) }}' x2='32' y2='{{ 40 + 2 * (100 - dbi.LOV) }}' style=\"stroke:rgb(255,0,0);stroke-width:2\" />");
{% endif %}
{% if dbi.HOV < 100.0 %}
  svg += ("<line x1='7' y1='{{ 40 + 2 * (100 - dbi.HOV) }}' x2='32' y2='{{ 40 + 2 * (100 - dbi.HOV) }}' style=\"stroke:rgb(255,0,0);stroke-width:2\" />");
{% endif %}

  svg += ("<!-- white SP bar-->");
*/
  svg += ("<rect x=\"60\" y=\"40\" width=\"20\" fill=\"#ffffff\" height=\"202\"/>");
  int bSP = 200 - int(2*PID1_SP);   // use SP in %
  svg += ("<rect x=\"61\" y=\"41\" width=\"18\" fill=\"#777777\" height=\""); svg += (bSP); svg += ("\"/>");
    
  svg += ("<rect x=\"100\" y=\"102\" width=\"93\"  height=\"21\" fill=\"#777777\" />"); //  <!-- SP text background rectangle -->"); use SP in EGU
  svg += ("<text x=\"150\" y=\"117\" font-family=\"Verdana\" font-size=\"12\" fill=\"white\"  text-anchor=\"middle\">"); svg += (PID1_RSP); svg += ("</text>");

  svg += ("<rect x=\"100\" y=\"126\" width=\"93\"  height=\"21\" fill=\"#777777\" />"); //  <!-- OV text background rectangle -->");
  svg += ("<text x=\"150\" y=\"141\" font-family=\"Verdana\" font-size=\"12\" fill=\"cyan\"  text-anchor=\"middle\">"); svg += (PID1_OV); svg += (" %</text>");

  svg += ("<rect x=\"100\" y=\"156\" width=\"93\"  height=\"21\" fill=\"#777777\" />"); //  <!-- MODE text background rectangle -->");
  svg += ("<text x=\"150\" y=\"172\" font-family=\"Verdana\" font-size=\"14\" fill=\"white\"  text-anchor=\"middle\">");
  svg += (PID1_tMD[int(PID1_MD)]);  svg += ("</text>");
  
  svg += ("</g>");   svg += ("</svg>\r\n");
  
return svg;  
}


#endif
