/***********************************************************************
 * Header File:
 *    TEST VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Unit tests for the Velocity class.
 ************************************************************************/

#pragma once

#include "unitTest.h"
#include "velocity.h"


 /*********************************************
  * TEST VELOCITY
  * Unit tests for Velocity
  *********************************************/
class TestVelocity : public UnitTest
{
public:
    void run()
    {

        constructor_default();
        constructor_nonDefault();
        getDX();
        getDY();
        setDX();
        setDY();

        addDX_zero();
        addDX_value();
        addDY_zero();
        addDY_value();


        report("Velocity");
    }

private:

    /*****************************************************************
     *****************************************************************
     * CONSTRUCTOR
     *****************************************************************
     *****************************************************************/


     /*********************************************
      * name:    DEFAULT CONSTRUCTOR
      * input:   nothing
      * output:  zero
      *********************************************/
    void constructor_default()
    {  // setup
       // exercise
        Velocity v;

        // verify
        assertEquals(v.dx, 0.0);
        assertEquals(v.dy, 0.0);
    }  // teardown

    /*********************************************
     * name:    NON DEFAULT CONSTRUCTOR
     * input:   2.3, 4.5
     * output:  (2.3, 4.5)
     *********************************************/
    void constructor_nonDefault()
    {  // setup
        double dx = 2.3;
        double dy = 4.5;

        // exercise
        Velocity v(dx, dy);

        // verify
        assertEquals(v.dx, 2.3);
        assertEquals(v.dy, 4.5);
        assertEquals(dx, 2.3);
        assertEquals(dy, 4.5);
    }  // teardown

    /*****************************************************************
     *****************************************************************
     * GETTERS
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    GET DX
      * input:   (2.3, 4.5)
      * output:  2.3
      *********************************************/
    void getDX()
    {  // setup
        Velocity v;
        v.dx = 2.3;
        v.dy = 4.5;
        double dx = 99.9;

        // exercise
        dx = v.getDX();

        // verify
        assertEquals(v.dx, 2.3);
        assertEquals(v.dy, 4.5);
        assertEquals(dx, 2.3);
    }  // teardown

    /*********************************************
     * name:    GET DY
     * input:   (2.3, 4.5)
     * output:  4.5
     *********************************************/
    void getDY()
    {  // setup
        Velocity v;
        v.dx = 2.3;
        v.dy = 4.5;
        double dy = 99.9;

        // exercise
        dy = v.getDY();

        // verify
        assertEquals(v.dx, 2.3);
        assertEquals(v.dy, 4.5);
        assertEquals(dy, 4.5);
    }  // teardown


    /*****************************************************************
     *****************************************************************
     * SETTERS
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    SET DX
      * input:   (99.9, 88.8) -1.1
      * output:  (-1.1, 88.8)
      *********************************************/
    void setDX()
    {  // setup
        Velocity v;
        v.dx = 99.9;
        v.dy = 88.8;
        double dx = -1.1;

        // exercise
        v.setDX(dx);

        // verify
        assertEquals(v.dx, -1.1);
        assertEquals(v.dy, 88.8);
        assertEquals(dx, -1.1);
    }  // teardown

    /*********************************************
     * name:    SET DY
     * input:   (99.9, 88.8) -1.1
     * output:  (99.9, -1.1)
     *********************************************/
    void setDY()
    {  // setup
        Velocity v;
        v.dx = 99.9;
        v.dy = 88.8;
        double dy = -1.1;

        // exercise
        v.setDY(dy);

        // verify
        assertEquals(v.dx, 99.9);
        assertEquals(v.dy, -1.1);
        assertEquals(dy, -1.1);
    }  // teardown


    /*****************************************************************
     *****************************************************************
     * ADD
     *****************************************************************
     *****************************************************************/

     /*********************************************
      * name:    ADD DX  zero
      * input:   (2.3, 4.5) 0.0
      * output:  (2.3, 4.5)
      *********************************************/
    void addDX_zero()
    {  // setup
        Velocity v;
        v.dx = 2.3;
        v.dy = 4.5;
        double dx = 0.0;

        // exercise
        v.addDX(dx);

        // verify
        assertEquals(v.dx, 2.3);
        assertEquals(v.dy, 4.5);
        assertEquals(dx, 0.0);
    }  // teardown

    /*********************************************
     * name:    ADD DX  VALUE
     * input:   (2.3, 4.5) 4.1
     * output:  (6.4, 4.5)
     *********************************************/
    void addDX_value()
    {  // setup
        Velocity v;
        v.dx = 2.3;
        v.dy = 4.5;
        double dx = 4.1;

        // exercise
        v.addDX(dx);

        // verify
        assertEquals(v.dx, 6.4);
        assertEquals(v.dy, 4.5);
        assertEquals(dx, 4.1);
    }  // teardown

    /*********************************************
     * name:    ADD DY  zero
     * input:   (2.3, 4.5) 0.0
     * output:  (2.3, 4.5)
     *********************************************/
    void addDY_zero()
    {  // setup
        Velocity v;
        v.dx = 2.3;
        v.dy = 4.5;
        double dy = 0.0;

        // exercise
        v.addDY(dy);

        // verify
        assertEquals(v.dx, 2.3);
        assertEquals(v.dy, 4.5);
        assertEquals(dy, 0.0);
    }  // teardown

    /*********************************************
     * name:    ADD DY  VALUE
     * input:   (2.3, 4.5) 4.1
     * output:  (2.3, 8.6)
     *********************************************/
    void addDY_value()
    {  // setup
        Velocity v;
        v.dx = 2.3;
        v.dy = 4.5;
        double dy = 4.1;

        // exercise
        v.addDY(dy);

        // verify
        assertEquals(v.dx, 2.3);
        assertEquals(v.dy, 8.6);
        assertEquals(dy, 4.1);
    }  // teardown
};
