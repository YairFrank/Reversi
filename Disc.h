//
// Created by yair on 05/11/17.
//

//Yair Frank 203699566

#ifndef TARGIL1_DISK_H
#define TARGIL1_DISK_H


class Disc {
public:
    /**
     * Default constructor
     */
    Disc ();
    /**
     * Constructor
     * @param row
     * @param column
     */
    Disc(int row, int column);
    /**
     * Constructor
     * @param disc
     * @param row
     * @param column
     */
    Disc (char disc, int row, int column);
    /**
     * Getter od disc's type.
     * @return
     */
    char getDisc ();
    /**
     * Getter of disc's row.
     * @return
     */
    int getDiscRow ();
    /**
     * Getter of disc's column.
     * @return
     */
    int getDiscColumn ();
    /**
     * Setter of disc.
     * @param disc
     */
    void setDisc(char disc);
private:
    char disc;
    int row, column;
};

#endif //TARGIL1_DISK_H