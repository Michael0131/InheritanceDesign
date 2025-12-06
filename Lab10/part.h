#pragma once

#include "destructibleEntity.h"

class Part : public DestructibleEntity
{
public:
   Part() = default;

   Part(const Position& inPos, const Velocity& inVel)
   {
      pos = inPos;
      v = inVel;
      alive = true;

      // e.g. wait 24 frames (half a second) before this part can collide
      collisionDelayFrames = 24;
   }

   virtual void draw(ogstream& gout) override = 0; // default

   // Let collision system know if this part is ready
   bool canCollide() const override
   {
      return alive && collisionDelayFrames <= 0;
   }

   // We need to decrement the delay each frame
   void update(double dt) override
   {
      // keep the normal physics from Entity
      Entity::update(dt);

      if (collisionDelayFrames > 0)
         --collisionDelayFrames;
   }

protected:
   // By default, parts do not spawn fragments unless overridden
   int fragmentCountOnBreakup() const override { return 0; }

private:
   int collisionDelayFrames = 0;  // counts down each frame
};


// --------------------------------------------------------------
// GPS Parts
// --------------------------------------------------------------
// 
//  - Center : drawGPSCenter(), radius 7 px, breaks into 3 fragments
//  - Left   : drawGPSLeft(),   radius 8 px, breaks into 3 fragments
//  - Right  : drawGPSRight(),  radius 8 px, breaks into 3 fragments
//

class GPSCenterPart : public Part
{
public:
   GPSCenterPart(const Position& p, const Velocity& vel)
      : Part(p, vel)
   {
      setRadius(7.0 * metersPerPixel);
   }

   void draw(ogstream& gout) override
   {
      gout.drawGPSCenter(pos, angle);
   }

protected:
   int fragmentCountOnBreakup() const override { return 3; }
};


class GPSLeftPart : public Part
{
public:
   GPSLeftPart(const Position& p, const Velocity& vel)
      : Part(p, vel)
   {
      setRadius(8.0 * metersPerPixel);
   }

   void draw(ogstream& gout) override
   {
      Position offset; // zero offset for detached part
      gout.drawGPSLeft(pos, angle, offset);
   }

protected:
   int fragmentCountOnBreakup() const override { return 3; }
};


class GPSRightPart : public Part
{
public:
   GPSRightPart(const Position& p, const Velocity& vel)
      : Part(p, vel)
   {
      setRadius(8.0 * metersPerPixel);
   }

   void draw(ogstream& gout) override
   {
      Position offset; // zero offset for detached part
      gout.drawGPSRight(pos, angle, offset);
   }

protected:
   int fragmentCountOnBreakup() const override { return 3; }
};

// Note: Sputnik only breaks into fragments, not parts

// --------------------------------------------------------------
// Hubble Parts
// --------------------------------------------------------------
//
//  - Telescope       : drawHubbleTelescope(), radius 10 px, breaks into 3 fragments
//  - Computer module : drawHubbleComputer(),  radius  7 px, breaks into 2 fragments
//  - Left array      : drawHubbleLeft(),      radius  8 px, breaks into 2 fragments
//  - Right array     : drawHubbleRight(),     radius  8 px, breaks into 2 fragments
//

class HubbleTelescopePart : public Part
{
public:
   HubbleTelescopePart(const Position& p, const Velocity& vel)
      : Part(p, vel)
   {
      setRadius(10.0 * metersPerPixel);
   }

   void draw(ogstream& gout) override
   {
      Position offset;   // detached: no offset from its own center
      gout.drawHubbleTelescope(pos, angle, offset);
   }

protected:
   int fragmentCountOnBreakup() const override { return 3; }
};


class HubbleComputerPart : public Part
{
public:
   HubbleComputerPart(const Position& p, const Velocity& vel)
      : Part(p, vel)
   {
      setRadius(7.0 * metersPerPixel);
   }

   void draw(ogstream& gout) override
   {
      Position offset;
      gout.drawHubbleComputer(pos, angle, offset);
   }

protected:
   int fragmentCountOnBreakup() const override { return 2; }
};


class HubbleLeftPart : public Part
{
public:
   HubbleLeftPart(const Position& p, const Velocity& vel)
      : Part(p, vel)
   {
      setRadius(8.0 * metersPerPixel);
   }

   void draw(ogstream& gout) override
   {
      Position offset;
      gout.drawHubbleLeft(pos, angle, offset);
   }

protected:
   int fragmentCountOnBreakup() const override { return 2; }
};


class HubbleRightPart : public Part
{
public:
   HubbleRightPart(const Position& p, const Velocity& vel)
      : Part(p, vel)
   {
      setRadius(8.0 * metersPerPixel);
   }

   void draw(ogstream& gout) override
   {
      Position offset;
      gout.drawHubbleRight(pos, angle, offset);
   }

protected:
   int fragmentCountOnBreakup() const override { return 2; }
};


// --------------------------------------------------------------
// CrewDragon Parts
// --------------------------------------------------------------
//
//  - Center : drawCrewDragonCenter(), radius 6 px, breaks into 4 fragments
//  - Left   : drawCrewDragonLeft(),   radius 6 px, breaks into 2 fragments
//  - Right  : drawCrewDragonRight(),  radius 6 px, breaks into 2 fragments
//

class CrewDragonCenterPart : public Part
{
public:
   CrewDragonCenterPart(const Position& p, const Velocity& vel)
      : Part(p, vel)
   {
      setRadius(6.0 * metersPerPixel);
   }

   void draw(ogstream& gout) override
   {
      gout.drawCrewDragonCenter(pos, angle);
   }

protected:
   int fragmentCountOnBreakup() const override { return 4; }
};


class CrewDragonLeftPart : public Part
{
public:
   CrewDragonLeftPart(const Position& p, const Velocity& vel)
      : Part(p, vel)
   {
      setRadius(6.0 * metersPerPixel);
   }

   void draw(ogstream& gout) override
   {
      Position offset;
      gout.drawCrewDragonLeft(pos, angle, offset);
   }

protected:
   int fragmentCountOnBreakup() const override { return 2; }
};


class CrewDragonRightPart : public Part
{
public:
   CrewDragonRightPart(const Position& p, const Velocity& vel)
      : Part(p, vel)
   {
      setRadius(6.0 * metersPerPixel);
   }

   void draw(ogstream& gout) override
   {
      Position offset;
      gout.drawCrewDragonRight(pos, angle, offset);
   }

protected:
   int fragmentCountOnBreakup() const override { return 2; }
};


// --------------------------------------------------------------
// Starlink Parts
// --------------------------------------------------------------
//
//  - Body  : drawStarlinkBody(),  radius 2 px, breaks into 3 fragments
//  - Array : drawStarlinkArray(), radius 4 px, breaks into 3 fragments
//
class StarlinkBodyPart : public Part
{
public:
   StarlinkBodyPart(const Position& p, const Velocity& vel)
      : Part(p, vel)
   {
      setRadius(2.0 * metersPerPixel);
   }

   void draw(ogstream& gout) override
   {
      Position offset;
      gout.drawStarlinkBody(pos, angle, offset);
   }

protected:
   int fragmentCountOnBreakup() const override { return 3; }
};


class StarlinkArrayPart : public Part
{
public:
   StarlinkArrayPart(const Position& p, const Velocity& vel)
      : Part(p, vel)
   {
      setRadius(4.0 * metersPerPixel);
   }

   void draw(ogstream& gout) override
   {
      Position offset;
      gout.drawStarlinkArray(pos, angle, offset);
   }

protected:
   int fragmentCountOnBreakup() const override { return 3; }
};