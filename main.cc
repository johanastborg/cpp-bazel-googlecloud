#include "google/cloud/storage/client.h"
#include <iostream>
#include <cstdlib>

int main() {
  auto project_id = std::getenv("GOOGLE_CLOUD_PROJECT");
  if (!project_id) {
    std::cerr << "GOOGLE_CLOUD_PROJECT environment variable is not set\n";
    return 1;
  }

  // Create a client to communicate with Google Cloud Storage.
  // By default, this uses the Application Default Credentials.
  auto options = google::cloud::Options{};
  auto client = google::cloud::storage::Client(options);

  int count = 0;
  try {
    for (auto&& bucket_metadata : client.ListBucketsForProject(project_id)) {
      if (!bucket_metadata) {
        std::cerr << "Error reading bucket metadata: " << bucket_metadata.status() << "\n";
        return 1;
      }

      std::cout << bucket_metadata->name() << "\n";
      ++count;
    }
  } catch (const std::exception& e) {
    std::cerr << "Exception caught: " << e.what() << "\n";
    return 1;
  }

  if (count == 0) {
    std::cout << "No buckets found in project " << project_id << "\n";
  }

  return 0;
}
