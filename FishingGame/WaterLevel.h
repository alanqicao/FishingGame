/*
 * Project: A9 - Educational App
 *
 * Github Repo: https://github.com/University-of-Utah-CS3505/a9-edu-app-f24-whohuong
 * Group Name: Costco Hotdog
 * Authors: Huong Tran, Qi Cao, Johnny Tran, Penny Chanthavong
 * Date: December 6, 2024
 */

#ifndef WATERLEVEL_H
#define WATERLEVEL_H

///
/// \brief The WaterLevel enum - Represents the different levels of water depth.
/// This class enum is used to classify the depth at which the lure and fishes are located in the body of water.
///
/// Each value corresponds to a specific depth level:
/// - SURFACE: Represents the topmost layer of water.
/// - MIDWATER: Represents the middle layer of water.
/// - DEEPWATER: Represents the bottommost layer of water, where the water is deepest.
///
enum class WaterLevel{
    SURFACE, // 650 - toppart that water does not occupy /  3
    MIDWATER,
    DEEPWATER
};

#endif // WATERLEVEL_H
