   M S B A M L   `   `   `  ����G  CASYD_Projekt, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null+clr-namespace:ASYD_ProjektASYD_Projekt  5   	       ASYD_Projekt.MainWindow   5   	   \ XPresentationFramework, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35R NWindowsBase, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35W SPresentationCore, Version=4.0.0.0, Culture=neutral, PublicKeyToken=31bf3856ad364e35D 9http://schemas.microsoft.com/winfx/2006/xaml/presentation    5   	   R NSystem.Xaml, Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089:x,http://schemas.microsoft.com/winfx/2006/xaml     5   	   @d2http://schemas.microsoft.com/expression/blend/2008     5   	   Jmc;http://schemas.openxmlformats.org/markup-compatibility/2006     5   	   ,localclr-namespace:ASYD_Projekt     5   	     � Title$  
MainWindow��5   	   $	��450��6   $	��800��6)   .��5	      �  � RowDefinitions 5
   
   �� 5      $��80 �6   �� 5      $	��24* �6   �� 5      $	��61* �6    � ColumnDefinitions 5   
   �� 5      $
��Auto �6   �� 5      .+�5   
   � $��0q�6    5      �� 5      $
��Auto �6#   �� 5      $	��118 �6#   �� 5      $	��118 �6#    5      �� 5      �� 5      .+�5      �� -   5         ��Name$ 	cbComPort��5      $��20��6*   $	��5,0q�66   $��Center=�6C   $��93��6^   $��1��6i   �� 5      -   5         ��Name$ label��5      $��COM Port��6#   $	��0,7q�66   $��Center=�6C   $��26��6^   �� 5      -   5         ��Name$ 
cmdConnect��5      $��connect��6)   $��1��6;   $��Center=�6K   $��24��6h   $��0q�6t   $��1��6   $��Center=�6�   $��80��6�   �� 5       -   5        $ 
cmdRefresh��5       $��refresh��6)   $��2��6;   $��Center=�6K   $��24��6h   $��0q�6t   $��Center=�6   $��62��6�   �� 5!      -   5        $ cmdDisconnect��5!      $��
disconnect��6,   $��2��6A   $��Center=�6Q   $��24��6n   $��0q�6z   $��1��6�   $��Center=�6�   $��80��6�   5"      �� 5#   
   -   5         ��Name$ txtCMD��5#      $��10q�6"   $��1��6.    �� TextWrapping$
 Wrap=�6;   5$      5%      