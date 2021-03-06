/******************************************************************************

   REBVO: RealTime Edge Based Visual Odometry For a Monocular Camera.
   Copyright (C) 2016  Juan José Tarrio

   Jose Tarrio, J., & Pedre, S. (2015). Realtime Edge-Based Visual Odometry
   for a Monocular Camera. In Proceedings of the IEEE International Conference
   on Computer Vision (pp. 702-710).

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

 *******************************************************************************/

#ifndef EDGE_TRACKER_H
#define EDGE_TRACKER_H

#include "edge_finder.h"
#include "UtilLib/NormalDistribution.h"
namespace  rebvo{

class edge_tracker : public edge_finder
{

    int nmatch;     //Number of matches

public:



    using edge_finder::edge_finder;

    void rotate_keylines(TooN::Matrix <3,3> RotF);


    int directed_matching(TooN::Vector <3> Vel, TooN::Matrix <3,3> RVel, TooN::Matrix <3,3> BackRot, edge_tracker *et0,int &kf_matchs, double min_thr_mod, double min_thr_ang, double max_radius, double loc_uncertainty, bool stereo_mode, bool clear=false);

    int search_match(KeyLine &k,TooN::Vector <3> Vel,TooN::Matrix <3,3> RVel,TooN::Matrix <3,3> BackRot,double min_thr_mod,double min_thr_ang,double max_radius, double loc_uncertainty);

    int directed_matching_stereo(TooN::Vector <3> &tCam0toCam1, TooN::Matrix <3,3> &RCam0toCam1, edge_tracker *et_pair, double min_thr_mod, double min_thr_ang, double max_radius, double loc_uncertainty, double ReshapeQAbsolute, double ReshapeQRelative, double LocationUncertaintyModel);

    int search_match_stereo(KeyLine &k, TooN::Vector<3> &tCam0toCam1, TooN::Matrix<3, 3> &RCam0toCam1, cam_model &cam0, double min_thr_mod, double min_thr_ang, double max_radius, double loc_uncertainty, double ReshapeQAbsolute, double ReshapeQRelative, double LocationUncertaintyModel);


    int FordwardMatch(edge_tracker *et, bool clear=false);


    void UpdateInverseDepthKalman(TooN::Vector <3> vel, TooN::Matrix <3,3> RVel, TooN::Matrix <3,3> RW0, double ReshapeQAbsolute, double ReshapeQRelative, double LocationUncertainty);
    double UpdateInverseDepthKalman(KeyLine &kli, TooN::Vector <3> vel, TooN::Matrix <3,3> RVel, TooN::Matrix<3, 3> RW0, double ReshapeQAbsolute, double ReshapeQRelative, double LocationUncertainty);
    double UpdateInverseDepthKalmanSimple(KeyLine &kli, TooN::Vector <3> vel, TooN::Matrix <3,3> RVel, TooN::Matrix<3, 3> RW0, double ReshapeQAbsolute, double ReshapeQRelative, double LocationUncertainty);
    double UpdateInverseDepthKalmanARLU(KeyLine &kli, TooN::Vector <3> vel, double &rho, double &s_rho, double &rho0, double &s_rho0, double ReshapeQAbsolute, double LocationUncertainty);
    double EstimateQuantile(double s_rho_min, double s_rho_max, double percentile, int n);

    double EstimateReScaling(double &RKp, const double &s_rho_min, const uint &MatchNumMin, bool re_escale);
    double EstimateReScalingOpt(double &RKp, const double &s_rho_min, const uint &MatchNumMin, bool re_escale);



    bool ExtRotVel(TooN::Vector <3> &rot,TooN::Matrix <3,3> &RRot,TooN::Vector <3> &vel,TooN::Matrix <3,3> &RVel);

    int Regularize_1_iter(double thresh);

    int NumMatches(){return nmatch;}

    void DebugMatchHisto(uint m_num_max, uint bin_num, uint *histo);

    bool ExtRotVel(const TooN::Vector<3> &vel, TooN::Matrix<6, 6> &Wx, TooN::Matrix<6, 6> &Rx, TooN::Vector <6> &X, const double &LocUncert, double HubReweigth);
    static void BiasCorrect(TooN::Vector <6> &X,TooN::Matrix<6,6> &Wx,TooN::Vector <3> &Gb,TooN::Matrix<3,3> &Wb,const TooN::Matrix<3,3> &Rg,const TooN::Matrix<3,3> &Rb);

    double getDepthFromStereo(KeyLine &kl, KeyLine &kl_pair, cam_model &cam0, cam_model &cam1, TooN::Vector<3> &tCam0toCam1, TooN::Matrix<3, 3> &RCam0toCam1, double ReshapeQAbsolute, double ReshapeQRelative, double LocationUncertainty, double &I_rho);
    void fuseStereoDepth();
};

}


#endif // EDGE_TRACKER_H
