#pragma once
namespace Concerns {
  namespace AuthenticationStages {
     void stage_success() {
//      stage = session[:authentication_stages]&.first

//      if ( stage && stage.to_s == params[:stage]) {
//        if ( params[:secret] == stage_secrets[stage]) {
//          session[:authentication_stages] = session[:authentication_stages].drop(1)

//          successful_authentication User.find(session[:authenticated_user_id]), reset_stages: false
//        else
//          flash[:error] = I18n.t :notice_auth_stage_verification_error, stage: stage

//          redirect_to signin_path
//        }
//      else
//        flash[:error] = I18n.t(
//          :notice_auth_stage_wrong_stage,
//          expected: stage || '(none)',
//          actual: params[:stage]
//        )

//        redirect_to signin_path
//      }
    }

     void stage_failure() {
//      flash[:error] = flash[:error] || I18n.t(:notice_auth_stage_error, stage: params[:stage])

//      redirect_to signin_path
    }

//    private:

     void authentication_stages(bool after_activation = false, bool reset = true) {
//      if ( OpenProject::Authentication::Stage.stages.select(&:active?).any?) {
//        if ( reset) { session.delete [:authentication_stages, :stage_secrets, :back_url] ;}

//        if ( session.include?(:authentication_stages)) {
//          lookup_authentication_stages
//        else
//          init_authentication_stages after_activation: after_activation
//        }
//      else
//        []
//      }
    }

     void lookup_authentication_stages() {
//      OpenProject::Authentication::Stage.find_all session[:authentication_stages]
    }

//     void init_authentication_stages(after_activation:) {
//      stages = active_stages after_activation

//      session[:authentication_stages] = stages.map(&:identifier)
//      session[:stage_secrets] = new_stage_secrets

//      // Remember back_url from params since we're redirecting
//      // but don't use the referer
//      session[:back_url] = params[:back_url]

//      stages
//    }

//     void active_stages(after_activation) {
//      OpenProject::Authentication::Stage
//        .stages
//        .select(&:active?)
//        .select { |s| s.run_after_activation? || !after_activation }
//    }

//     void stage_secrets() {
//      Hash(session[:stage_secrets])
//    }

//     void new_stage_secrets() {
//      session[:authentication_stages]
//        .map { |ident| [ident, stage_secret(ident)] }
//        .to_h
//    }

//     void stage_secret(ident) {
//      SecureRandom.hex(16)
//    }
  }
}
