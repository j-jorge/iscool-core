#include <iscool/system/haptic_feedback.hpp>

#include <iscool/jni/get_static_method.hpp>
#include <iscool/jni/static_method_void.hpp>

iscool::system::haptic_feedback::haptic_feedback()
  : m_enabled(false)
{}

bool iscool::system::haptic_feedback::is_enabled() const
{
  return m_enabled;
}

void iscool::system::haptic_feedback::set_enabled(bool enabled)
{
  m_enabled = enabled;
}

void iscool::system::haptic_feedback::click()
{
  if (!m_enabled)
    return;

  const iscool::jni::static_method<void> method(
      iscool::jni::get_static_method<void>(
          "iscool/system/HapticFeedbackService", "click", "()V"));

  method();
}
