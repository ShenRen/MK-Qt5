/********************************************************************
* Copyright (C) 2012 - 2015 ArcEye <arceye AT mgware DOT co DOT uk>
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
********************************************************************/


#include "qtlatency.h"


qtlatency::qtlatency(int argc, char** argv)
{
Q_UNUSED( argc )
QString str = "qtlatency", str2 = argv[1];

	if(argv[1] == NULL)
        {
        qDebug() << "Syntax: loadusr qtlatency {path-to-ui-file}\n";
        exit(-1);
        }
    
    panel = new qtPanel(this, str, str2 );

}

