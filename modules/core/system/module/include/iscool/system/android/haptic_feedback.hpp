#pragma once

namespace iscool::system
{
  class haptic_feedback
  {
  public:
    haptic_feedback();

    bool is_enabled() const;
    void set_enabled(bool enabled);

    void click();

  private:
    bool m_enabled;
  };
}
