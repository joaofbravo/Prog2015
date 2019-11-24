#ifndef __GB_STYLES_H__
#define __GB_STYLES_H__ 1

typedef enum
  {
    Sty_Msg1, Sty_About1, Sty_About2, Sty_TitleMain, Sty_Button1, Sty_Frame1, Sty_Frame2,
    Sty_End } StyleNameEnum ;

typedef struct
{
  gchar     *font        ;
  GdkRGBA   *bg_normal   ;
  GdkRGBA   *bg_prelight ;
  GdkRGBA   *fg_normal   ;
  GdkRGBA   *fg_prelight ;

  // (??) Old versions
  //  GdkColor  *bg_normal   ;
  //  GdkColor  *bg_prelight ;
  //  GdkColor  *fg_normal   ;
  //  GdkColor  *fg_prelight ;
} StylesStruct ;

extern StylesStruct **
gb_styles_new (void);

extern void
gb_widget_style_set (GtkWidget    *w   ,
                     StylesStruct *sty );

#endif /* __GB_STYLES_H__ */
