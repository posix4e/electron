// Copyright (c) 2013 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef BRAVE_BROWSER_BRAVE_CONTENT_BROWSER_CLIENT_H_
#define BRAVE_BROWSER_BRAVE_CONTENT_BROWSER_CLIENT_H_

#include <string>
#include <vector>

#include "atom/browser/atom_browser_client.h"

namespace content {
class PlatformNotificationService;
class NavigationHandle;
}

#if defined(ENABLE_EXTENSIONS)
namespace extensions {
class AtomBrowserClientExtensionsPart;
}
#endif

namespace brave {

class BraveContentBrowserClient : public atom::AtomBrowserClient {
 public:
  BraveContentBrowserClient();
  virtual ~BraveContentBrowserClient();

  std::string GetAcceptLangs(content::BrowserContext* browser_context) override;
  std::string GetApplicationLocale() override;
  void SetApplicationLocale(std::string locale);

 protected:
  // content::ContentBrowserClient:
  void RegisterRenderFrameMojoInterfaces(
      shell::InterfaceRegistry* registry,
      content::RenderFrameHost* render_frame_host) override;
  void RenderProcessWillLaunch(content::RenderProcessHost* host) override;
  void AppendExtraCommandLineSwitches(base::CommandLine* command_line,
                                      int child_process_id) override;
  content::PlatformNotificationService*
      GetPlatformNotificationService() override;
  void OverrideWebkitPrefs(content::RenderViewHost* host,
      content::WebPreferences* prefs) override;
  bool CanCreateWindow(const GURL& opener_url,
                       const GURL& opener_top_level_frame_url,
                       const GURL& source_origin,
                       WindowContainerType container_type,
                       const GURL& target_url,
                       const content::Referrer& referrer,
                       const std::string& frame_name,
                       WindowOpenDisposition disposition,
                       const blink::WebWindowFeatures& features,
                       bool user_gesture,
                       bool opener_suppressed,
                       content::ResourceContext* context,
                       int render_process_id,
                       int opener_render_view_id,
                       int opener_render_frame_id,
                       bool* no_javascript_access) override;
  bool ShouldUseProcessPerSite(content::BrowserContext* browser_context,
                                       const GURL& effective_url) override;
  void GetAdditionalAllowedSchemesForFileSystem(
      std::vector<std::string>* additional_allowed_schemes) override;
  void GetAdditionalWebUISchemes(
      std::vector<std::string>* additional_schemes) override;
  bool ShouldAllowOpenURL(content::SiteInstance* site_instance,
                                      const GURL& url) override;
  void BrowserURLHandlerCreated(
      content::BrowserURLHandler* handler) override;
  void SiteInstanceGotProcess(
      content::SiteInstance* site_instance) override;
  void SiteInstanceDeleting(
      content::SiteInstance* site_instance) override;
  bool ShouldSwapBrowsingInstancesForNavigation(
      content::SiteInstance* site_instance,
      const GURL& current_url,
      const GURL& new_url) override;
  std::string GetStoragePartitionIdForSite(
      content::BrowserContext* browser_context,
      const GURL& site) override;
  void GetStoragePartitionConfigForSite(
    content::BrowserContext* browser_context,
      const GURL& site,
      bool can_be_default,
      std::string* partition_domain,
      std::string* partition_name,
      bool* in_memory) override;
  GURL GetEffectiveURL(
      content::BrowserContext* browser_context, const GURL& url) override;
  base::FilePath GetShaderDiskCacheDirectory() override;
  gpu::GpuChannelEstablishFactory* GetGpuChannelEstablishFactory() override;

void RegisterInProcessMojoApplications(StaticMojoApplicationMap* apps) override;
void RegisterOutOfProcessMojoApplications(
    OutOfProcessMojoApplicationMap* apps) override;


  ScopedVector<content::NavigationThrottle> CreateThrottlesForNavigation(
      content::NavigationHandle* handle) override;

 protected:
  bool IsValidStoragePartitionId(
    content::BrowserContext* browser_context,
    const std::string& partition_id);


 private:
#if defined(ENABLE_EXTENSIONS)
  std::unique_ptr<extensions::AtomBrowserClientExtensionsPart> extensions_part_;
#endif

  DISALLOW_COPY_AND_ASSIGN(BraveContentBrowserClient);
};

}  // namespace brave

#endif  // BRAVE_BROWSER_BRAVE_CONTENT_BROWSER_CLIENT_H_
